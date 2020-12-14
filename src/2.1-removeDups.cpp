#include "util/LinkedList.h"
#include <gtest/gtest.h>
#include <unordered_set>

// Of course this would be best solved with sort & unique, which would happen in place
// without the need for additional buffer
// This solution uses additional buffer to store seen elements. The list.erase() method has been
// given optional parameter which is a hint to the 'previous' iterator. This way the algorithm
// has NlogN complexity (due to the 'seen' buffer) instead of N^2 when the 'previous' iterator
// would need to be found each time

template <typename T>
void removeDups(util::LinkedList<T>& list)
{
  std::unordered_set<T> seen;

  if (list.empty())
    return;

  auto it = list.begin();
  seen.insert(*it);
  ++it;

  auto follower = list.begin();

  for (; it != list.end();)
    if (auto [_, inserted] = seen.insert(*it); !inserted) {
      it = list.erase(it, follower);
    }
    else {
      ++it;
      ++follower;
    }
}

TEST(RemoveDupsTest, allUnique)
{
  util::LinkedList<int> l;
  l.pushFront(1);
  l.pushFront(2);
  l.pushFront(3);

  removeDups(l);

  std::vector const expected = {3, 2, 1};
  EXPECT_EQ(expected, l);
}

TEST(RemoveDupsTest, complexCase)
{
  util::LinkedList<int> l;

  // 121331241
  l.pushFront(1);
  l.pushFront(4);
  l.pushFront(2);
  l.pushFront(1);
  l.pushFront(3);
  l.pushFront(3);
  l.pushFront(1);
  l.pushFront(2);
  l.pushFront(1);

  removeDups(l);

  std::vector const expected = {1, 2, 3, 4};
  EXPECT_EQ(expected, l);
}

TEST(RemoveDupsTest, allTheSame)
{
  util::LinkedList<int> l;
  l.pushFront(1);
  l.pushFront(1);
  l.pushFront(1);

  removeDups(l);

  std::vector const expected = {1};
  EXPECT_EQ(expected, l);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
