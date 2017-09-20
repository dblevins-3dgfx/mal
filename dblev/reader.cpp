#include <regex>
#include <iostream>
#include <assert.h>

#include "reader.h"

/////////////////////////////////////////////////////////////////////////////////
const MalDataPtr reader::read_str(const str_t& str)
{ 
        reader rdr;
        
        rdr.tokenizer(str);
        MalDataPtr ast = rdr.read_form();

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
void reader::tokenizer(const str_t& str)
{
        static const std::regex re("[\\s,]*(~@|[\\[\\]{}()'`~^@]|\"(?:\\\\.|[^\\\\\"])*\"|;.*|[^\\s\\[\\]{}('\"`,;)]*)");
        std::smatch match;

        auto tstr = str;
        while (!tstr.empty() && std::regex_search(tstr, match, re))
        {
                token_t tok = match.str();
	        trim(tok);
                m_token_list.push_back(tok);
                tstr = match.suffix().str();
        }

        m_curr_tok = m_token_list.begin();
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr reader::read_form()
{
        MalDataPtr result;

        if (isOpenParen(peek()))
        {
                next(); // discard "("
                result = read_list();
                next(); // discard ")"
        }
        else
        {
                result = read_atom();
        }

        return result;
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr reader::read_list()
{
        auto list = std::make_shared<MalList>();
        while (!isCloseParen(peek()))
        {
                auto form = read_form();
                list->Add(form);
        }

        return list;
}

/////////////////////////////////////////////////////////////////////////////////
MalDataPtr reader::read_atom()
{
        MalDataPtr result = nullptr;

        token_t tok = next();
        if (isNum(tok))
        {
                result = std::make_shared<MalNumber>(tok);
        }
        else
        {
                result = std::make_shared<MalSymbol>(tok);
        }

        return result;
}

