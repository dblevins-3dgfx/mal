#include <string>
#include <iostream>

/*
--- step0_repl ----------------------------------
READ(str): return str

EVAL(ast,env): return ast

PRINT(exp): return exp

rep(str): return PRINT(EVAL(READ(str),""))

main loop: println(rep(readline("user> ")))
*/

typedef std::string str_t;
typedef std::string ast_t;
typedef std::string env_t;
typedef std::string exp_t;

str_t READ(str_t str);
exp_t EVAL(ast_t ast, env_t env);
exp_t PRINT(exp_t exp);
exp_t rep(str_t str);

//////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  while (true)
  {
    std::cout << "user> ";
    str_t str;
    std::getline(std::cin, str);
    std::cout << rep(str) << std::endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////
str_t READ(str_t str)
{
  return str;
}

//////////////////////////////////////////////////////////////////////////////////
exp_t EVAL(ast_t ast, env_t env)
{
  return ast;
}

//////////////////////////////////////////////////////////////////////////////////
exp_t PRINT(exp_t exp)
{
  return exp;
}

//////////////////////////////////////////////////////////////////////////////////
exp_t rep(str_t str)
{
  return PRINT(EVAL(READ(str),""));
}

