#include <iostream>
#include <array>

struct LetterCounter
{
  void operator()(std::string_view const input)
  {
     for (char const symbol : input)
     {
       std::uint8_t idx = static_cast<std::uint8_t>(symbol);
       counts[idx]++;
     }
  }
  
  bool operator==(LetterCounter const& rhs) const
  {
    return counts == rhs.counts;
  }
  
private:
  std::array<std::size_t, 256> counts = {0};
};

int main()
{
  std::string_view stringA = "Test world";
  std::string_view stringB = "world Test";
  
  LetterCounter lhs, rhs;
  lhs(stringA);
  rhs(stringB);
  
  std::cout << "The two strings are " << (lhs == rhs ? "" : "not ") << "a permutation of each other" << std::endl;
  
  return 0;
}