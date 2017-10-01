#include <iostream>

#include "types.h"
#include "reader.h"
#include "printer.h"

const MalDataPtr READ(const std::string& str);
const MalDataPtr EVAL(const MalDataPtr ast, const Env& env);
const std::string PRINT(const MalDataPtr exp);
const std::string rep(const std::string& str);

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
  try
  {
    return PRINT(EVAL(READ(str), Env()));
  }
  catch (int)
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
const MalDataPtr EVAL(const MalDataPtr ast, const Env&)
{
  return ast;
}

//////////////////////////////////////////////////////////////////////////////////
const std::string PRINT(const MalDataPtr exp)
{
  return Printer::pr_str(exp);
}
