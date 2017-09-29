#include <iostream>
#include <assert.h>
#include <regex>

#include "reader.h"
#include "regex_strings.h"

/////////////////////////////////////////////////////////////////////////////////
const MalDataPtr CReader::readStr(const str_t& str)
{
  CReader rdr;

  rdr.tokenizer(str);
  MalDataPtr ast = rdr.readForm();

  return ast;
}

/////////////////////////////////////////////////////////////////////////////////
void CReader::tokenizer(const str_t& str)
{
  static const std::regex re(LISP_REGEXP);

  mTokenList.insert(mTokenList.end(),
  	            std::sregex_token_iterator(str.begin(), str.end(), re, 1),
  		    std::sregex_token_iterator());
  for(auto tok : mTokenList)
    {
      std::cout << tok << std::endl;
    }
  mCurrTok = mTokenList.begin();
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr CReader::readForm()
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
MalDataPtr CReader::readList()
{
  auto list = std::make_shared<CMalList>();
  while (!isCloseParen(peek()))
  {
    auto form = readForm();
    list->Add(form);
  }

  return list;
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr CReader::readAtom()
{
  MalDataPtr result = nullptr;

  token_t tok = next();
  if (isNum(tok))
  {
    result = std::make_shared<CMalNumber>(tok);
  }
  else
  {
    result = std::make_shared<CMalSymbol>(tok);
  }

  return result;
}

/////////////////////////////////////////////////////////////////////////////////
bool CReader::isNum(const token_t& tok) const
{
  static const std::regex re(INTEGER_REGEXP);
  return std::regex_match(tok, re);
}

