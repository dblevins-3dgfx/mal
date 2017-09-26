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

  class CToken
  {
  public:
    CToken(const std::string& val)
    {
      mValue = val;
    }

    bool isOpenParen() const
    {
      return mValue == "(";
    }

    bool isCloseParen() const
    {
      return mValue == ")";
    }

    bool isNum() const;

    std::string str()
    {
      return mValue;
    }

  private:
    std::string mValue;
  };

  typedef std::vector<CToken> token_list_t;
  typedef std::vector<CToken>::iterator token_list_iterator_t;

  CToken next()
  {
    assert(mCurrTok != mTokenList.end());
    CToken result = *mCurrTok;
    mCurrTok++;
    return result;
  }

  CToken peek()
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
