#pragma once

#include <memory>
#include <map>

#include "types.h"

class Env;

class Env
{
public:
  Env(Env* outer = nullptr) : mOuter(outer) {}
  void Set(const MalSymbol& sym, const MalDataPtr val);
  Env* Find(const MalSymbol& sym);
  MalDataPtr Get(const MalSymbol& sym);

private:
  Env* mOuter;
  std::map< MalSymbol, MalDataPtr > mData;
};
