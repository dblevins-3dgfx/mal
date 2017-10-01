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

  virtual const MalList*     GetMalList() const { return nullptr; }
  virtual const MalSymbol*   GetMalSymbol() const { return nullptr; }
  virtual const MalNumber*   GetMalNumber() const { return nullptr; }
  virtual const MalFunction* GetMalFunction() const { return nullptr; }

};
typedef std::shared_ptr<MalData> MalDataPtr;


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
  MalDataPtr First() const
  {
    return mList[0];
  }
  MalDataPtr Rest() const
  {
    auto result = std::make_shared<MalList>();
    for (auto i = mList.begin() + 1; i != mList.end(); i++)
    {
      result->Add(*i);
    }
    return result;
  }

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
  const MalSymbol* GetMalSymbol() const override { return this; }
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
  int GetValue() const { return mNum;  }
  const MalNumber* GetMalNumber() const override { return this; }

private:
  int mNum;
};


class MalFunction final : public MalData
{
public:
  typedef std::function< MalDataPtr(MalDataPtr) > Func;
  MalFunction(const Func& f)
  {
    mFunc = f;
  }
  MalType GetType() override { return function; }
  MalDataPtr Call(MalDataPtr args) const { return mFunc(args); }
  const MalFunction* GetMalFunction() const override { return this; }

private:
  Func mFunc;
};

typedef std::map< MalSymbol, MalDataPtr > Env;
