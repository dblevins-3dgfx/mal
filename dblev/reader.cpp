#include <iostream>
#include <assert.h>
#include <regex>

#include "reader.h"

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
  static const std::regex re("[\\s,]*(~@|[\\[\\]{}()'`~^@]|\"(?:\\\\.|[^\\\\\"])*\"|;.*|[^\\s\\[\\]{}('\"`,;)]*)");

  mTokenList.insert(mTokenList.end(),
		    std::sregex_token_iterator(str.begin(), str.end(), re, 1),
		    std::sregex_token_iterator());
  mCurrTok = mTokenList.begin();
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr CReader::readForm()
{
  MalDataPtr result;

  if (peek().isOpenParen())
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
  while (!peek().isCloseParen())
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

  CToken tok = next();
  if (tok.isNum())
  {
    result = std::make_shared<CMalNumber>(tok.Str());
  }
  else
  {
    result = std::make_shared<CMalSymbol>(tok.Str());
  }

  return result;
}
