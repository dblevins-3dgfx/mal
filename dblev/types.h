#pragma once

#include <memory>
#include <string>
#include <vector>
#include <assert.h>

typedef std::string str_t;
typedef std::string env_t;

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
		list
	};

	virtual ~MalData() {};
	virtual MalType GetType() { return nil; }
	virtual const MalList* GetMalList() const { return nullptr; }
	virtual const str_t GetPrStr() { return "nil";  }
};


class MalList final : public MalData
{
public:
	typedef std::vector<MalDataPtr> MalDataPtrList;
	void Add(MalDataPtr data)
	{
		m_list.push_back(data);
	}
	MalType GetType() override { return list; } 
    const MalList* GetMalList() const override { return this; }
	const MalDataPtrList& GetList() const { return m_list; }

private:
	MalDataPtrList m_list;
};


class MalSymbol final : public MalData
{
public:
	MalSymbol(str_t str) :
		m_str(str)
	{}
	MalType GetType() override { return symbol; }
	const str_t GetPrStr() override  { return m_str; }
private:
	str_t   m_str;
};

class MalNumber final : public MalData
{
public:
	MalNumber(str_t str) :
		m_num(atoi(str.c_str()))
	{}

	MalType GetType() override { return number; }
	const str_t GetPrStr() override { char buffer[16];  return str_t(itoa(m_num, buffer, 10)); }

private:
	int m_num;
};


