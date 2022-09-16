#include "gtest/gtest.h"
#include "matrix.hpp"

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
TEST(MatrixRAII_Tests, CopyAssignmentTest) {
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
TEST(MatrixRAII_Tests, SequenceCtorTest) {
  int m = 5, n = 6;
  std::vector<int> seq(m * n);
  for (int i = 0; i < m * n; i++) {
    seq[i] = i;
  }

  Matrix<int> matrix{m, n, seq.begin(), seq.end()};
  for (int i = 0, a = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      EXPECT_EQ(matrix[i][j], seq[a]);
      a++;
    }
  }
}

TEST(MatrixRAII_TemplateTest, CopyAssignmentTest) {
  //Equal
  std::shared_ptr<int> ip = std::make_shared<int>(0);
  Matrix<std::shared_ptr<int>> m1(5, 5, ip);
  Matrix<std::shared_ptr<int>> m2(5, 5, ip);
  Matrix<std::shared_ptr<int>> m3;
  Matrix<std::shared_ptr<int>> m4;
  m3 = m1;
  m4 = m2;
  EXPECT_EQ(m3, m4);

  //Not Equal
  Matrix<std::shared_ptr<int>> m5(5, 5, std::make_shared<int>(0));
  Matrix<std::shared_ptr<int>> m6(5, 5, std::make_shared<int>(0));
  Matrix<std::shared_ptr<int>> m7(1, 1, std::make_shared<int>(0));
  Matrix<std::shared_ptr<int>> m8(1, 1, std::make_shared<int>(0));
  m7 = m5;
  m8 = m6;
  EXPECT_NE(m7, m8);
}

TEST(MatrixMethotsTests, DeleteRowTest) {
  int m = 5, n = 6;
  std::vector<int> seq(m * n);
  for (int i = 0; i < m * n; i++) {
    seq[i] = i;
  }

  Matrix<int> matrix{m, n, seq.begin(), seq.end()};
  int deleted_row = 1;
  int offset_row = 0;
  matrix.DeleteRow(deleted_row);
  for (int i = 0, a = 0; i < m - 1; i++) {
    if (i == deleted_row)
      offset_row = n;
    for (int j = 0; j < n; j++) {
      EXPECT_EQ(matrix[i][j], seq[a + offset_row]);
      a++;
    }
  }
}
TEST(MatrixMethotsTests, DeleteColumnTest) {
  int m = 5, n = 6;
  std::vector<int> seq(m * n);
  for (int i = 0; i < m * n; i++) {
    seq[i] = i;
  }

  Matrix<int> matrix{m, n, seq.begin(), seq.end()};
  int deleted_col = 3;
  matrix.DeleteColumn(deleted_col);
  for (int i = 0, a = 0; i < m; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (j == deleted_col)
        a++;
      EXPECT_EQ(matrix[i][j], seq[a]);
      a++;
    }
  }
}
TEST(MatrixMethotsTests, DeleteRowColumnTest) {
  int m = 5, n = 6;
  std::vector<int> seq(m * n);
  for (int i = 0; i < m * n; i++) {
    seq[i] = i;
  }

  Matrix<int> matrix{m, n, seq.begin(), seq.end()};
  int deleted_row = 3;
  int deleted_col = 4;
  int offset_row = 0;
  matrix.DeleteRowColumn(deleted_row, deleted_col);
  for (int i = 0, a = 0; i < m - 1; i++) {
    if (i == deleted_row)
      offset_row = n;
    for (int j = 0; j < n - 1; j++) {
      if (j == deleted_col)
        a++;
      EXPECT_EQ(matrix[i][j], seq[a + offset_row]);
      a++;
    }
  }
}