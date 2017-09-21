#pragma once

#include <vector>
#include <cctype>
#include <algorithm>

#include "types.h"

/////////////////////////////////////////////////////////////////////////////////
class CReader
{
public:

  static const MalDataPtr readStr(const str_t& str);

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
    assert(mCurrTok != mTokenList.end());
    token_t result = *mCurrTok;
    mCurrTok++;
    return result;
  }

  token_t peek()
  {
    assert(mCurrTok != mTokenList.end());
    return *mCurrTok;
  }


  void tokenizer(const str_t& str);
  MalDataPtr readForm();
  MalDataPtr readList();
  MalDataPtr readAtom();

  token_list_t mTokenList;
  token_list_iterator_t mCurrTok;
};
