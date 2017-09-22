#include <regex>
#include <iostream>
#include <assert.h>

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
  std::smatch match;

  auto tstr = str;
  while (!tstr.empty() && std::regex_search(tstr, match, re))
  {
    CToken tok(match.str());
    mTokenList.push_back(tok);
    tstr = match.suffix().str();
  }

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


