#pragma once

#include "types.h"

/////////////////////////////////////////////////////////////////////////////////
class reader
{
 public:

  static const ast_t& read_str(const str_t& str) { return str; }

 private:
  typedef std::string token_t;
  
  token_t next();
  token_t peek();

  reader();
};
