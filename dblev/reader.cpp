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


namespace {
  const char* ws = " \t\n\r\f\v";
  std::string& rtrim(std::string& s, const char* t = ws)
  {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
  }

  std::string& ltrim(std::string& s, const char* t = ws)
  {
    s.erase(0, s.find_first_not_of(t));
    return s;
  }

  std::string& trim(std::string& s, const char* t = ws)
  {
    return ltrim(rtrim(s, t), t);
  }
}

/////////////////////////////////////////////////////////////////////////////////
void CReader::tokenizer(const str_t& str)
{
  static const std::regex re("[\\s,]*(~@|[\\[\\]{}()'`~^@]|\"(?:\\\\.|[^\\\\\"])*\"|;.*|[^\\s\\[\\]{}('\"`,;)]*)");
  std::smatch match;

  auto tstr = str;
  while (!tstr.empty() && std::regex_search(tstr, match, re))
  {
    token_t tok = match.str();
    trim(tok);
    mTokenList.push_back(tok);
    tstr = match.suffix().str();
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


