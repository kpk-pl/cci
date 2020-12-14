#include <gtest/gtest.h>
#include "util/LinkedList.h"

TEST(ReturnKthToLast, previousElement)
{
  util::LinkedList<int> l;
  l.pushFront(3);
  l.pushFront(2);
  l.pushFront(1);

  auto it = ++l.begin();
  EXPECT_EQ(1, *l.kthTo(1, it));
}

TEST(ReturnKthToLast, handlesEmptyList)
{
  util::LinkedList<int> l;
  EXPECT_EQ(l.end(), l.kthTo(1, l.begin()));
}

TEST(ReturnKthToLast, fromEnd)
{
  util::LinkedList<int> l;
  l.pushFront(3);
  l.pushFront(2);
  l.pushFront(1);

  EXPECT_EQ(1, *l.kthTo(3, l.end()));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

