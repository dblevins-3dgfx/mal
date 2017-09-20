#include "printer.h"

/////////////////////////////////////////////////////////////////////////////////
const str_t printer::pr_str(const MalDataPtr ast)
{
  str_t result = "";

  if (auto list = ast->GetMalList())
  {
    result += "(";
    bool first = true;
    for (auto e : list->GetList())
    {
      if (first)
      {
        first = false;
      }
      else
      {
        result += " ";
      }
      result += pr_str(e);
    }
    result += ")";
  }
  else
  {
    result += ast->GetPrStr();
  }

  return result;
}

