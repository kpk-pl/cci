#include <iostream>

bool isUnique(std::string_view const input)
{
  bool seen[256] = {0};

  for (char const symbol : input)
  {
    std::uint8_t idx = static_cast<std::uint8_t>(symbol);
    if (seen[idx]) {
      return false;
    }
    else {
      seen[idx] = true;
    }
  }

  return true;
}

int main()
{
  char const input[] = "Unique_symbol";
  std::cout << std::boolalpha << isUnique(input) << std::endl;
  return 0;
}
