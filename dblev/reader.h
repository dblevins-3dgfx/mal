#pragma once

#include <vector>
#include <cctype>
#include <algorithm>

#include "types.h"

/////////////////////////////////////////////////////////////////////////////////
class reader
{
 public:

  static const MalDataPtr read_str(const str_t& str);

 private:
  typedef std::string token_t;
  typedef std::vector<token_t> token_list_t;
  typedef std::vector<token_t>::iterator token_list_iterator_t;

  static bool isOpenParen(const token_t& tok)
  {
	  return tok == "(";
  }

  static bool isCloseParen(const token_t& tok)
  {
	  return tok == ")";
  }

  static bool isNum(const token_t& tok)
  {
	  return !tok.empty() && std::find_if(tok.begin(), tok.end(), [](char c) 
	  { 
		  return !std::isdigit(c); 
	  }) == tok.end();
  }

  token_t next()
  { 
	  assert(m_curr_tok != m_token_list.end());
	  token_t result = *m_curr_tok;
	  m_curr_tok++; 
	  return result;
  }

  token_t peek() 
  { 
	  assert(m_curr_tok != m_token_list.end());
	  return *m_curr_tok;
  }


  void tokenizer(const str_t& str);
  MalDataPtr read_form();
  MalDataPtr read_list();
  MalDataPtr read_atom();

  token_list_t m_token_list;
  token_list_iterator_t m_curr_tok;
};
