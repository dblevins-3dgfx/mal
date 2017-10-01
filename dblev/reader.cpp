#include <iostream>
#include <assert.h>
#include <regex>

#include "reader.h"
#include "regex_strings.h"

/////////////////////////////////////////////////////////////////////////////////
const MalDataPtr Reader::readStr(const std::string& str)
{
  Reader rdr;

  rdr.tokenizer(str);
  MalDataPtr ast = rdr.readForm();

  return ast;
}

/////////////////////////////////////////////////////////////////////////////////
void Reader::tokenizer(const std::string& str)
{
  static const std::regex re(LISP_REGEXP);

  mTokenList.insert(mTokenList.end(),
                    std::sregex_token_iterator(str.begin(), str.end(), re, 1),
                    std::sregex_token_iterator());
  mCurrTok = mTokenList.begin();
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr Reader::readForm()
{
  MalDataPtr result;

  if (isOpenParen(peek()))
  {
    next(); // discard "("
    result = readList();
    next(); // discard ")"
  }
  else
  {
    result = readAtom();
  }

  return result;
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr Reader::readList()
{
  auto list = std::make_shared<MalList>();
  while (!isCloseParen(peek()))
  {
    auto form = readForm();
    list->Add(form);
  }

  return list;
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr Reader::readAtom()
{
  MalDataPtr result = nullptr;

  token_t tok = next();
  if (isNum(tok))
  {
    result = std::make_shared<MalNumber>(tok);
  }
  else
  {
    result = std::make_shared<MalSymbol>(tok);
  }

  return result;
}

/////////////////////////////////////////////////////////////////////////////////
bool Reader::isNum(const token_t& tok) const
{
  static const std::regex re(INTEGER_REGEXP);
  return std::regex_match(tok, re);
}

