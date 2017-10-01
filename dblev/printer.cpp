#include "printer.h"

/////////////////////////////////////////////////////////////////////////////////
const std::string Printer::pr_str(const MalDataPtr ast)
{
  std::string result = "";

  if (auto list = ast->GetMalList())
  {
    result += "(";
    bool first = true;
    for (const auto& e : list->GetList())
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

