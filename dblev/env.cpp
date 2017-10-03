#include "env.h"

/////////////////////////////////////////////////////////////////////////////////
void Env::Set(const MalSymbol& sym, const MalDataPtr val)
{
  mData[sym] = val;
}

/////////////////////////////////////////////////////////////////////////////////
Env* Env::Find(const MalSymbol& sym) 
{
  Env* result = nullptr;

  auto iter = mData.find(sym);
  if (iter != mData.end())
  {
    result = this;
  }
  else if (mOuter != nullptr)
  {
    result = mOuter->Find(sym);
  }

  return result;
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr Env::Get(const MalSymbol& sym)
{
  MalDataPtr result;
  Env* env = Find(sym);
  if (env != nullptr)
  {
    result = env->mData[sym];
  }
  else
  {
    result = std::make_shared<MalData>();
  }
  return result;
}
