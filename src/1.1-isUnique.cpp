#include <iostream>
#include <gtest/gtest.h>

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

TEST(IsUniqueTest, JustUniqueLetters)
{
  ASSERT_TRUE(isUnique("Unique_symbol"));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
