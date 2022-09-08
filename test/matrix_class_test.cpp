#include "gtest/gtest.h"
#include "matrix.h"

using namespace testing;

TEST(MatrixOperatorsTests, EqualsTest) {
  //Equal
  Matrix<int> m(5, 5, 0);
  EXPECT_EQ(m, m);

  Matrix<int> m1(5, 5, 0);
  Matrix<int> m2(5, 5, 0);
  EXPECT_EQ(m1, m2);

  //Not Equal
  Matrix<int> m3(5, 5, 0);
  Matrix<int> m4(6, 6, 0);
  EXPECT_NE(m3, m4);

  Matrix<int> m5(5, 5, 0);
  Matrix<int> m6(5, 5, 1);
  EXPECT_NE(m5, m6);
}
TEST(MatrixOperatorsTests, SquareBracketsTest) {
  const Matrix<int> m1(5, 5, 1);
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      EXPECT_EQ(m1[i][j], 1);

  Matrix<int> m2(5, 5, 1);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      m2[i][j] = i + j;
      EXPECT_EQ(m2[i][j], i + j);
    }
  }
}

TEST(MatrixRAII_Tests, CopyConstructorTest) {
  //Equal
  Matrix<int> m1(5, 5, 0);
  Matrix<int> m2 = m1;
  EXPECT_EQ(m1, m2);

  //Not Equal
  Matrix<int> m3(5, 5, 1);
  Matrix<int> m4(m2);
  EXPECT_NE(m3, m4);
}
TEST(MatrixRAII_Tests, CopyAsignmentTest) {
  //Equal
  Matrix<int> m1(5, 5, 0);
  Matrix<int> m2(5, 5, 0);
  Matrix<int> m3;
  Matrix<int> m4;
  m3 = m1;
  m4 = m2;
  EXPECT_EQ(m3, m4);

  //Not Equal
  Matrix<int> m5(5, 5, 0);
  Matrix<int> m6(5, 5, 1);
  Matrix<int> m7(1, 1, 1);
  Matrix<int> m8(1, 1, 1);
  m7 = m5;
  m8 = m6;
  EXPECT_NE(m7, m8);
}
TEST(MatrixRAII_Tests, MoveConstructorTest) {
  //Equal
  Matrix<int> m1= Matrix<int>(5, 5,0);
  Matrix<int> m2(Matrix<int>(5, 5, 0));
  EXPECT_EQ(m1, m2);

  Matrix<int> m3(std::move(m1));
  Matrix<int> m4 = std::move(m2);
  EXPECT_EQ(m3, m4);

  //Not Equal
  Matrix<int> m5 = Matrix<int>(5, 5, 0);
  Matrix<int> m6(Matrix<int>(5, 5,1));
  EXPECT_NE(m5, m6);

  Matrix<int> m7(std::move(m5));
  Matrix<int> m8 = std::move(m6);
  EXPECT_NE(m7, m8);
}
TEST(MatrixRAII_Tests, MoveAsignmentTest) {
  //Equal
  Matrix<int> m1(5, 5, 0);
  Matrix<int> m3;
  Matrix<int> m4;
  m3 = std::move(m1);
  m4 = Matrix<int>(5, 5, 0);
  EXPECT_EQ(m3, m4);

  //Not Equal
  Matrix<int> m5(5, 5, 0);
  Matrix<int> m7(1, 1);
  Matrix<int> m8(1, 1);
  m7 = std::move(m5);
  m8 = Matrix<int> (5, 5, 1);
  EXPECT_NE(m7, m8);
}