#include <gtest/gtest.h>
#include <array>
#include <set>

template<std::size_t N, std::size_t M>
using Matrix = std::array<std::array<int, M>, N>;

template<std::size_t N, std::size_t M>
void zeroMatrix(Matrix<N,M> &matrix)
{
  std::set<std::size_t> zeroCols, zeroRows;
  for (std::size_t n = 0; n < N; ++n)
    for (std::size_t m = 0; m < M; ++m)
      if (matrix[n][m] == 0)
      {
        zeroCols.insert(n);
        zeroRows.insert(m);
      }

  for (std::size_t const& n : zeroCols)
    for (std::size_t m = 0; m < M; ++m)
      matrix[n][m] = 0;

  for (std::size_t const& m : zeroRows)
    for (std::size_t n = 0; n < N; ++n)
      matrix[n][m] = 0;
}

TEST(ZeroMatrixTest, justWorks)
{
  Matrix<3,4> matrix;
  matrix[0] = {2,4,-1,6};
  matrix[1] = {8,0,-1,4};
  matrix[2] = {3,6,1,0};

  zeroMatrix(matrix);

  EXPECT_EQ(2, matrix[0][0]);
  EXPECT_EQ(0, matrix[0][1]);
  EXPECT_EQ(-1, matrix[0][2]);
  EXPECT_EQ(0, matrix[0][3]);

  EXPECT_EQ(0, matrix[1][0]);
  EXPECT_EQ(0, matrix[1][1]);
  EXPECT_EQ(0, matrix[1][2]);
  EXPECT_EQ(0, matrix[1][3]);

  EXPECT_EQ(0, matrix[2][0]);
  EXPECT_EQ(0, matrix[2][1]);
  EXPECT_EQ(0, matrix[2][2]);
  EXPECT_EQ(0, matrix[2][3]);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
