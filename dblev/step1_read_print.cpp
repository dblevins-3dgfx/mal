#include <iostream>

#include "types.h"
#include "reader.h"
#include "printer.h"

const MalDataPtr READ(const str_t& str);
const MalDataPtr EVAL(const MalDataPtr ast, const env_t& env);
const str_t PRINT(const MalDataPtr exp);
const str_t rep(const str_t& str);

/////////////////////////////////////////////////////////////////////////////////
int main(int, char**)
{
  const std::string prompt("user> ");
  while (true)
  {
    std::cout << prompt;
    str_t str;
    std::getline(std::cin, str);
    std::cout << rep(str) << std::endl;
  }
}

/////////////////////////////////////////////////////////////////////////////////
const str_t rep(const str_t& str)
{
  return PRINT(EVAL(READ(str), ""));
}

/////////////////////////////////////////////////////////////////////////////////
const MalDataPtr READ(const str_t& str)
{
  return CReader::readStr(str);
}

/////////////////////////////////////////////////////////////////////////////////
const MalDataPtr EVAL(const MalDataPtr ast, const env_t&)
{
  return ast;
}

//////////////////////////////////////////////////////////////////////////////////
const str_t PRINT(const MalDataPtr exp)
{
  return CPrinter::pr_str(exp);
}
