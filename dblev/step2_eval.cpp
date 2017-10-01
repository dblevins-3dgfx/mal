#include <iostream>

#include "types.h"
#include "reader.h"
#include "printer.h"

const MalDataPtr READ(const std::string& str);
const MalDataPtr EVAL(const MalDataPtr ast, const Env& env);
const std::string PRINT(const MalDataPtr exp);
const std::string rep(const std::string& str);
const MalDataPtr eval_ast(const MalDataPtr ast, const Env& env);

/////////////////////////////////////////////////////////////////////////////////
int main(int, char**)
{
  const std::string prompt("user> ");
  while (true)
  {
    std::cout << prompt;
    std::string str;
    std::getline(std::cin, str);
    std::cout << rep(str) << std::endl;
  }
}

/////////////////////////////////////////////////////////////////////////////////
const std::string rep(const std::string& str)
{
  Env repl_env = {
    {
      MalSymbol("+"), std::make_shared<MalFunction>(
      [](MalDataPtr args)
      {
        auto arglist = args->GetMalList()->GetList();
        int sum = 0;
        for (auto arg : arglist)
        {
          sum += arg->GetMalNumber()->GetValue();
        }
        return std::make_shared<MalNumber>(sum);
      }
    ) },

    {
      MalSymbol("-"), std::make_shared<MalFunction>(
      [](MalDataPtr args)
      {
        auto arglist = args->GetMalList()->GetList();
        int diff = 0;
        for (auto arg : arglist)
        {
          diff -= arg->GetMalNumber()->GetValue();
        }
        return std::make_shared<MalNumber>(diff);
      }
    ) },

   {
      MalSymbol("*"), std::make_shared<MalFunction>(
      [](MalDataPtr args)
      {
        auto arglist = args->GetMalList()->GetList();
        int prod = 0;
        for (auto arg : arglist)
        {
          prod *= arg->GetMalNumber()->GetValue();
        }
        return std::make_shared<MalNumber>(prod);
      }
    ) },

    {
      MalSymbol("-"), std::make_shared<MalFunction>(
      [](MalDataPtr args)
      {
        auto arglist = args->GetMalList()->GetList();
        int div = 0;
        for (auto arg : arglist)
        {
          div /= arg->GetMalNumber()->GetValue();
        }
        return std::make_shared<MalNumber>(div);
      }
    ) },
  };

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
const MalDataPtr EVAL(const MalDataPtr ast, const Env& env)
{
  MalDataPtr result = ast;

  if (ast->GetType() != MalData::list)
  {
    result = eval_ast(ast, env);
  }
  else
  {
    if (ast->GetMalList()->GetList().empty())
    {
      result = ast;
    }
    else {
      MalDataPtr evaluated = eval_ast(ast, env);
      auto list = evaluated->GetMalList();
      auto f = list->First()->GetMalFunction();
      result = f->Call(list->Rest());
    }
  }

  return result;
}

const MalDataPtr eval_ast(const MalDataPtr ast, const Env& env)
{
  MalDataPtr result = ast;

  if (ast->GetType() == MalData::symbol)
  {
    result = env.at(*(ast->GetMalSymbol()));
  }
  else if (ast->GetType() == MalData::list)
  {
    auto list = std::make_shared<MalList>();

    for (auto elem : ast->GetMalList()->GetList())
    {
      list->Add(EVAL(elem, env));
    }

    result = list;
  }

  return result;
}

//////////////////////////////////////////////////////////////////////////////////
const std::string PRINT(const MalDataPtr exp)
{
  return Printer::pr_str(exp);
}

