#include <array>
#include <gtest/gtest.h>

template <std::size_t N>
using Image = std::array<std::array<std::uint32_t, N>, N>;

template <std::size_t N>
void rotateInPlace(Image<N> &image) {
  std::size_t const halfNUp = (N + 1) / 2;
  std::size_t const halfNDn = N / 2;

  // iterate over one fourth of the image, rotating 4 pixels at a time
  // for images with odd number of pixels on each side, pick the
  // rectangle with X-asix bigger by one pixel than Y-axis, which
  // will cover entire square, apart from middle pixel, which is left
  // intact and should stay at its place
  for (std::size_t x = 0; x < halfNUp; ++x) {
    for (std::size_t y = 0; y < halfNDn; ++y) {
      std::uint32_t temp = image[x][y];
      image[x][y] = image[N - y - 1][x];
      image[N - y - 1][x] = image[N - x - 1][N - y - 1];
      image[N - x - 1][N - y - 1] = image[y][N - x - 1];
      image[y][N - x - 1] = temp;
    }
  }
}

TEST(RotationTest, oneElementArray) {
  Image<1> image = {{{5}}};
  rotateInPlace(image);
  EXPECT_EQ(5u, image[0][0]);
}

TEST(RotationTest, squareTwo) {
  /*
   *   [ 1 2 ]
   *   [ 3 4 ]
   */
  Image<2> image = {1, 2, {3, 4}};
  rotateInPlace(image);

  EXPECT_EQ(3u, image[0][0]);
  EXPECT_EQ(1u, image[0][1]);
  EXPECT_EQ(4u, image[1][0]);
  EXPECT_EQ(2u, image[1][1]);

  /*
   *   [ 3 1 ]
   *   [ 4 2 ]
   */
}

TEST(RotationTest, threeByThree) {
  /*
   * [ 1 2 3 ]
   * [ 4 5 6 ]
   * [ 7 8 9 ]
   */

  Image<3> image = {1, 2, 3, {4, 5, 6}, {7, 8, 9}};
  rotateInPlace(image);

  EXPECT_EQ(7u, image[0][0]);
  EXPECT_EQ(4u, image[0][1]);
  EXPECT_EQ(1u, image[0][2]);
  EXPECT_EQ(8u, image[1][0]);
  EXPECT_EQ(5u, image[1][1]);
  EXPECT_EQ(2u, image[1][2]);
  EXPECT_EQ(9u, image[2][0]);
  EXPECT_EQ(6u, image[2][1]);
  EXPECT_EQ(3u, image[2][2]);

  /*
   * [ 7 4 1 ]
   * [ 8 5 2 ]
   * [ 9 6 3 ]
   */
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
