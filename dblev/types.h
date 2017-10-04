#pragma once

#include <memory>
#include <string>
#include <vector>
#include <assert.h>
#include <map>
#include <functional>

class MalData;
class MalList;
class MalSymbol;
class MalNumber;
class MalFunction;

typedef std::shared_ptr<MalData> MalDataPtr;
typedef std::shared_ptr<MalList> MalListPtr;
typedef std::shared_ptr<MalSymbol> MalSymbolPtr;
typedef std::shared_ptr<MalNumber> MalNumberPtr;
typedef std::shared_ptr<MalFunction> MalFunctionPtr;

enum ErrorCode
{
  INCOMPLETE_SEXPR = 0,
  UNDEFINED_SYMBOL
};

/////////////////////////////////////////////////////////////////////////////////
class MalData
{
public:
  enum MalType {
    nil,
    symbol,
    number,
    list,
    function
  };

  virtual ~MalData() {};
  virtual MalType GetType() { return nil; }
  virtual const std::string GetPrStr() { return "nil"; }
};



/////////////////////////////////////////////////////////////////////////////////
class MalSymbol final : public MalData
{
public:
  MalSymbol(std::string str) :
    mStr(str)
  {}

  MalSymbol(MalDataPtr d)
  {
    if (auto ds = dynamic_cast<MalSymbol*>(d.get()))
    {
      mStr = ds->mStr;
    }
  }

  MalType GetType() override { return symbol; }
  const std::string GetPrStr() override { return mStr; }
  bool operator<(const MalSymbol& s) const { return mStr < s.mStr; }
  bool operator==(const MalSymbol& s) const { return mStr == s.mStr; }

private:
  std::string   mStr;
};

/////////////////////////////////////////////////////////////////////////////////
class MalList final : public MalData
{
public:
  typedef std::vector<MalDataPtr> MalDataPtrList;
  typedef MalDataPtrList::iterator iterator;

  MalList() {}

  MalList(MalDataPtr d)
  {
    if (auto dl = dynamic_cast<MalList*>(d.get()))
    {
      mList = dl->mList;
    }
  }

  MalType GetType() override { return list; }

  MalDataPtr First() const
  {
    return mList[0];
  }

  MalListPtr Rest() const
  {
    MalListPtr result = std::make_shared<MalList>();
    for (auto i = mList.begin() + 1; i != mList.end(); i++)
    {
      result->push_back(*i);
    }
    return result;
  }

  bool isSpecial(std::string key) const
  {
    bool result = false;
    if (mList[0]->GetType() == symbol)
    {
      result = (MalSymbol(mList[0]) == MalSymbol(key));
    }
    return result;
  }

  // Basic Container stuff
  iterator begin() { return mList.begin(); }
  iterator end() { return mList.end(); }
  MalDataPtr operator[](int idx) { return mList[idx]; }
  bool empty() { return mList.empty(); }
  size_t size() { return mList.size(); }
  void push_back(MalDataPtr data) { mList.push_back(data); }

private:
  MalDataPtrList mList;
};

/////////////////////////////////////////////////////////////////////////////////
class MalNumber final : public MalData
{
public:
  MalNumber(std::string str) :
    mNum(atoi(str.c_str()))
  {}

  MalNumber(int num) :
    mNum(num)
  {}

  MalNumber(MalDataPtr d)
  {
    if (auto dn = dynamic_cast<MalNumber*>(d.get()))
    {
      mNum = dn->mNum;
    }
    else
    {
      mNum = 0;
    }
  }


  MalType GetType() override { return number; }
  const std::string GetPrStr() override { return std::string(std::to_string(mNum)); }

  // int conversion
  operator int() {
    return mNum;
  }

private:
  int mNum;
};

/////////////////////////////////////////////////////////////////////////////////
class MalFunction final : public MalData
{
public:
  typedef std::function< MalDataPtr(MalListPtr) > Func;
  MalFunction(const Func& f)
  {
    mFunc = f;
  }

  MalFunction(MalDataPtr d)
  {
    if (auto df = dynamic_cast<MalFunction*>(d.get()))
    {
      mFunc = df->mFunc;
    }
  }

  MalType GetType() override { return function; }
  MalDataPtr Call(MalListPtr args) const { return mFunc(args); }

private:
  Func mFunc;
};
