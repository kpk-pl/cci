#include <gtest/gtest.h>
#include <string>
#include <string_view>

std::string compress(std::string_view input)
{
  std::string result;

  if (input.empty())
    return result;

  for (std::size_t pos = 0; pos < input.size(); )
  {
    std::size_t otherChar = input.find_first_not_of(input[pos], pos);
    if (otherChar == std::string::npos)
      otherChar = input.size();

    std::size_t const count = otherChar - pos;

    result += input[pos];
    result += std::to_string(count);

    pos += count;
  }

  if (result.size() < input.size())
    return result;
  return std::string(input);
}

TEST(StringCompressionTest, CompressesString)
{
  ASSERT_EQ("a2b1c5a3", compress("aabcccccaaa"));
}

TEST(StringCompressionTest, ReturnsOriginalIfShorter)
{
  ASSERT_EQ("abcd", compress("abcd"));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
