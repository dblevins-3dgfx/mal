#include <iostream>

#include "types.h"
#include "reader.h"
#include "printer.h"
#include "env.h"

const MalDataPtr READ(const std::string& str);
const MalDataPtr EVAL(const MalDataPtr ast, Env& env);
const std::string PRINT(const MalDataPtr exp);
const std::string rep(const std::string& str, Env& repl_env);
const MalDataPtr eval_ast(const MalDataPtr ast, Env& env);
void InitializeEnv(Env& repl_env);

/////////////////////////////////////////////////////////////////////////////////
int main(int, char**)
{
  const std::string prompt("user> ");

  Env repl_env;
  InitializeEnv(repl_env);

  while (true)
  {
    std::cout << prompt;
    std::string str;
    std::getline(std::cin, str);
    std::cout << rep(str, repl_env) << std::endl;
  }
}

/////////////////////////////////////////////////////////////////////////////////
void InitializeEnv(Env& repl_env)
{
  repl_env.Set(MalSymbol("+"), std::make_shared<MalFunction>(
    [](MalListPtr args)
  {
    auto arglist = args->GetList();
    int result = MalNumber(arglist[0]).GetValue();
    for (MalList::MalDataPtrList::iterator arg = arglist.begin() + 1; arg != arglist.end(); arg++)
    {
      result += MalNumber(*arg).GetValue();
    }
    return std::make_shared<MalNumber>(result);
  }));

  repl_env.Set(MalSymbol("-"), std::make_shared<MalFunction>(
    [](MalListPtr args)
  {
    auto arglist = args->GetList();
    int result = MalNumber(arglist[0]).GetValue();
    for (MalList::MalDataPtrList::iterator arg = arglist.begin() + 1; arg != arglist.end(); arg++)
    {
      result -= MalNumber(*arg).GetValue();
    }
    return std::make_shared<MalNumber>(result);
  }));

  repl_env.Set(MalSymbol("*"), std::make_shared<MalFunction>(
    [](MalListPtr args)
  {
    auto arglist = args->GetList();
    int result = MalNumber(arglist[0]).GetValue();
    for (MalList::MalDataPtrList::iterator arg = arglist.begin() + 1; arg != arglist.end(); arg++)
    {
      result *= MalNumber(*arg).GetValue();
    }
    return std::make_shared<MalNumber>(result);
  }));

  repl_env.Set(MalSymbol("/"), std::make_shared<MalFunction>(
    [](MalListPtr args)
  {
    auto arglist = args->GetList();
    int result = MalNumber(arglist[0]).GetValue();
    for (MalList::MalDataPtrList::iterator arg = arglist.begin() + 1; arg != arglist.end(); arg++)
    {
      result /= MalNumber(*arg).GetValue();
    }
    return std::make_shared<MalNumber>(result);
  }));
}

/////////////////////////////////////////////////////////////////////////////////
const std::string rep(const std::string& str, Env& repl_env)
{
  try
  {
    return PRINT(EVAL(READ(str), repl_env));
  }
  catch (...)
  {
    return "Error";
  }
}

/////////////////////////////////////////////////////////////////////////////////
const MalDataPtr READ(const std::string& str)
{
    return Reader::readStr(str);
}

/////////////////////////////////////////////////////////////////////////////////
const MalDataPtr EVAL(const MalDataPtr ast, Env& env)
{
  MalDataPtr result = ast;

  if (ast->GetType() != MalData::list)
  {
    result = eval_ast(ast, env);
  }
  else
  {
    if (MalList(ast).GetList().empty())
    {
      result = ast;
    }
    else if (MalList(ast).isSpecial("def!"))
    {
      MalSymbol s(MalList(ast).GetList()[1]);
      result = EVAL(MalList(ast).GetList()[2], env);
      env.Set(s, result);
    }
    else if (MalList(ast).isSpecial("let*"))
    {
      Env let_env(&env);
      auto symlist = MalList(MalList(ast).GetList()[1]).GetList();
      for (auto i = symlist.begin(); i != symlist.end(); i += 2)
      {
        MalSymbol sym(*i);
        auto val = *(i + 1);
        let_env.Set(sym, EVAL(val, let_env));
      }
      result = EVAL(MalList(ast).GetList()[2], let_env);
    }
    else {
      MalDataPtr evaluated = eval_ast(ast, env);
      MalList list(evaluated);
      if (list.First()->GetType() == MalData::function)
      {
        MalFunction f(list.First());
        result = f.Call(list.Rest());
      }
      else
      {
        throw UNDEFINED_SYMBOL;
      }
    }
  }

  return result;
}

const MalDataPtr eval_ast(const MalDataPtr ast, Env& env)
{
  MalDataPtr result = ast;

  if (ast->GetType() == MalData::symbol)
  {
    result = env.Get(MalSymbol(ast));
  }
  else if (ast->GetType() == MalData::list)
  {
    MalList list(ast);
    auto elist = std::make_shared<MalList>();

    for (auto elem : list.GetList())
    {
      elist->Add(EVAL(elem, env));
    }

    result = elist;
  }

  return result;
}

//////////////////////////////////////////////////////////////////////////////////
const std::string PRINT(const MalDataPtr exp)
{
  return Printer::pr_str(exp);
}

