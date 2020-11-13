#include <iostream>

bool oneAwayReplaced(std::string_view lhs, std::string_view rhs)
{
  bool replaced = false;
  for (std::size_t idx = 0; idx < lhs.size(); ++idx)
  {
    if (lhs[idx] != rhs[idx])
    {
      if (replaced)
        return false;
      replaced = true;
    }
  }
  
  return true;
}

bool oneAwayDeletion(std::string_view lhs, std::string_view rhs) 
{
  bool deleted = false;
  for (std::size_t idx = 0; idx < rhs.size(); ++ idx)
  {
    if (lhs[idx - (deleted ? 1 : 0)] != rhs[idx])
    {
      if (deleted)
        return false;
      deleted = true;
    }
  }
  
  return true;
}

bool oneAway(std::string_view lhs, std::string_view rhs)
{
  if (lhs.size() == rhs.size())
    return oneAwayReplaced(lhs, rhs);
  else if (lhs.size() < rhs.size())
  {
    if (rhs.size() - lhs.size() == 1)
      return oneAwayDeletion(lhs, rhs);
    else
      return false;
  }
  else
  {
    if (lhs.size() - rhs.size() == 1)
      return oneAwayDeletion(rhs, lhs);
    else
      return false;
  }
}

int main() {
  std::cout << "pale, ple " << std::boolalpha << oneAway("pale", "ple") << std::endl;
  std::cout << "pales, pale " << std::boolalpha << oneAway("pales", "pale") << std::endl;
  std::cout << "pale, bale " << std::boolalpha << oneAway("pale", "bale") << std::endl;
  std::cout << "pale, bake " << std::boolalpha << oneAway("pale", "bake") << std::endl;
  return 0; 
}