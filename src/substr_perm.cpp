#include <iostream>
#include <string>
#include <string_view>
#include <numeric>

/*
Find all positions in string b where there is a permutation of string s
Complexity O(len(B))
*/

std::string const s = "abbc";
std::string const b = "cbabadcbbabbcbabaabccbabc";

int main() {
  if (s.size() > b.size())
    return 0;
  if (s.empty())
    return 0;

  auto const xorLetter = [](std::uint8_t const result, char const element) { return result ^ element; };

  auto const sXor = std::accumulate(s.begin(), s.end(), 0, xorLetter);
  std::uint8_t rollingXor = std::accumulate(b.begin(), b.begin() + s.size() - 1, 0, xorLetter);

  for (unsigned i = 0; i < b.size() - s.size() + 1; ++i)
  {
    rollingXor ^= b[i + s.size() - 1];
    std::uint8_t const result = sXor ^ rollingXor;
    if (result == 0)
      std::cout << i << ": " << std::string_view(b.data() + i, s.length()) << std::endl;

    rollingXor ^= b[i];
  }
}
