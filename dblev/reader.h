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
      trim(mValue);
    }

    bool isOpenParen() const
    {
      return mValue == "(";
    }

    bool isCloseParen() const
    {
      return mValue == ")";
    }

    bool isNum() const
    {
      return !mValue.empty() && std::find_if(mValue.begin(), mValue.end(), [](char c)
      {
        return !std::isdigit(c);
      }) == mValue.end();
    }

    std::string Str()
    {
      return mValue;
    }

  private:
    const char* ws = " \t\n\r\f\v";

    std::string& rtrim(std::string& s)
    {
      s.erase(s.find_last_not_of(ws) + 1);
      return s;
    }

    std::string& ltrim(std::string& s)
    {
      s.erase(0, s.find_first_not_of(ws));
      return s;
    }

    std::string& trim(std::string& s)
    {
      return ltrim(rtrim(s));
    }

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
