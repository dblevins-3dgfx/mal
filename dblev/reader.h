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

  token_t next()
  {
    if (mCurrTok == mTokenList.end())
    {
      throw EOF;
    }
    token_t result = *mCurrTok;
    mCurrTok++;
    return result;
  }

  token_t peek()
  {
    if (mCurrTok == mTokenList.end())
    {
      throw EOF;
    }
    return *mCurrTok;
  }


  void tokenizer(const str_t& str);
  MalDataPtr readForm();
  MalDataPtr readList();
  MalDataPtr readAtom();

  bool isOpenParen(const token_t& tok) const
  {
    return tok == "(";
  }

  bool isCloseParen(const token_t& tok) const
  {
    return tok == ")";
  }
  bool isNum(const token_t& tok) const;

  token_list_t mTokenList;
  token_list_iterator_t mCurrTok;
};
