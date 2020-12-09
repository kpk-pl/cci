#include <gtest/gtest.h>
#include <string>

bool checkRotation(std::string const &a, std::string const &b) {
  if (a.size() != b.size())
    return false;

  // given a = waterbottle
  // and b = erbottlewat
  // temp = erbottlewaterbottlewat
  std::string const temp = b + b;

  // pos = 8 because we can find a in temp
  auto pos = temp.find(a);

  // if we did not find a in temp, then the string pair does not fulfill
  // requirements
  return pos != std::string::npos;
}

TEST(StringRotationTest, singleLetter) {
  EXPECT_TRUE(checkRotation("a", "a"));
  EXPECT_FALSE(checkRotation("a", "b"));
}

TEST(StringRotationTest, waterbottle) {
  EXPECT_TRUE(checkRotation("waterbottle", "erbottlewat"));
}

TEST(StringRotationTest, theSame) {
  EXPECT_TRUE(checkRotation("thesame", "thesame"));
}

TEST(StringRotationTest, substringButNoRotation) {
  EXPECT_FALSE(checkRotation("abc", "abcabc"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
