#include <gtest/gtest.h>
#include "util/LinkedList.h"

TEST(DeleteMiddleTest, removesMiddle)
{
  util::LinkedList<int> l;
  l.pushFront(3);
  l.pushFront(2);
  l.pushFront(1);

  l.erase(++l.begin());

  auto it = l.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(l.end(), it);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

