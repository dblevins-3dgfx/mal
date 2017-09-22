#pragma once

#include <memory>
#include <string>
#include <vector>
#include <assert.h>

typedef std::string str_t;
typedef std::string env_t;

class CMalData;
class CMalList;
typedef std::shared_ptr<CMalData> MalDataPtr;

class CMalData
{
public:
  enum MalType {
    nil,
    symbol,
    number,
    list
  };

  virtual ~CMalData() {};
  virtual MalType GetType() { return nil; }
  virtual const CMalList* GetMalList() const { return nullptr; }
  virtual const str_t GetPrStr() { return "nil"; }
};


class CMalList final : public CMalData
{
public:
  typedef std::vector<MalDataPtr> MalDataPtrList;
  void Add(MalDataPtr data)
  {
    mList.push_back(data);
  }
  MalType GetType() override { return list; }
  const CMalList* GetMalList() const override { return this; }
  const MalDataPtrList& GetList() const { return mList; }

private:
  MalDataPtrList mList;
};


class CMalSymbol final : public CMalData
{
public:
  CMalSymbol(str_t str) :
    mStr(str)
  {}
  MalType GetType() override { return symbol; }
  const str_t GetPrStr() override { return mStr; }
private:
  str_t   mStr;
};

class CMalNumber final : public CMalData
{
public:
  CMalNumber(str_t str) :
    mNum(atoi(str.c_str()))
  {}

  MalType GetType() override { return number; }
  const str_t GetPrStr() override { return str_t(std::to_string(mNum)); }

private:
  int mNum;
};



