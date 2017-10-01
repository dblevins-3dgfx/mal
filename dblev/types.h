#pragma once

#include <memory>
#include <string>
#include <vector>
#include <assert.h>
#include <map>
#include <functional>

class MalData;
class MalList;
typedef std::shared_ptr<MalData> MalDataPtr;

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
  virtual const MalList* GetMalList() const { return nullptr; }
  virtual const std::string GetPrStr() { return "nil"; }
};


class MalList final : public MalData
{
public:
  typedef std::vector<MalDataPtr> MalDataPtrList;
  void Add(MalDataPtr data)
  {
    mList.push_back(data);
  }
  MalType GetType() override { return list; }
  const MalList* GetMalList() const override { return this; }
  const MalDataPtrList& GetList() const { return mList; }

private:
  MalDataPtrList mList;
};


class MalSymbol final : public MalData
{
public:
  MalSymbol(std::string str) :
    mStr(str)
  {}
  MalType GetType() override { return symbol; }
  const std::string GetPrStr() override { return mStr; }
  bool operator<(const MalSymbol& s) const { return mStr < s.mStr; }
private:
  std::string   mStr;
};

class MalNumber final : public MalData
{
public:
  MalNumber(std::string str) :
    mNum(atoi(str.c_str()))
  {}
  MalNumber(int num) :
    mNum(num)
  {}

  MalType GetType() override { return number; }
  const std::string GetPrStr() override { return std::string(std::to_string(mNum)); }
  int GetValue() { return mNum;  }

private:
  int mNum;
};


class MalFunction final : public MalData
{
public:
  typedef std::function< MalNumber(MalNumber, MalNumber) > NumericFunc;
  MalFunction(const NumericFunc& f)
  {
    mFunc = f;
  }
  MalType GetType() override { return function; }
  MalNumber Call(MalNumber a, MalNumber b) { return mFunc(a, b); }

private:
  NumericFunc mFunc;
};

typedef std::map< MalSymbol, MalDataPtr > Env;
