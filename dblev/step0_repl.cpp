#include <string>
#include <iostream>

typedef std::string str_t;
typedef std::string ast_t;
typedef std::string env_t;
typedef std::string exp_t;

const str_t& READ(const str_t& str);
const exp_t& EVAL(const ast_t& ast, const env_t& env);
const exp_t& PRINT(const exp_t& exp);
const exp_t& rep(const str_t& str);

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
const exp_t& rep(const str_t& str)
{
  return PRINT(EVAL(READ(str),""));
}

/////////////////////////////////////////////////////////////////////////////////
const str_t& READ(const str_t& str)
{
  return str;
}

/////////////////////////////////////////////////////////////////////////////////
const exp_t& EVAL(const ast_t& ast, const env_t&)
{
  return ast;
}

//////////////////////////////////////////////////////////////////////////////////
const exp_t& PRINT(const exp_t& exp)
{
  return exp;
}


