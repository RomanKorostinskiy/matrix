#include "gtest/gtest.h"
#include "matrix.hpp"
#include <iostream>
#include <fstream>

using namespace testing;

std::string GetResourcesPath() {
  std::string cur_file = __FILE__;
  std::string cur_dir  = cur_file.substr(0, cur_file.find_last_of('/') + 1);
  return cur_dir + "/../resources/";
}

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
  //Valid construction
  {
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

  //Invalid construction
  {
    int m = 5, n = 6;
    int sz = m * n + 1;
    std::vector<int> seq(sz, 0);
    EXPECT_THROW({
      Matrix<int> matrix(m, n, seq.begin(), seq.end());
      }, std::range_error);
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

TEST(MatrixMethodsTests, DeleteRowTest) {
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
TEST(MatrixMethodsTests, DeleteColumnTest) {
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
TEST(MatrixMethodsTests, DeleteRowColumnTest) {
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
TEST(MatrixMethodsTests, RecursiveDetTestInt) {
  //Exceptional test
  {
    Matrix<int> matrix(5, 7, 0);
    EXPECT_THROW({
                   matrix.RecursiveDet();
                 }, std::domain_error);
  }
  //2x2
  {
    std::string test_filepath = GetResourcesPath() +
        "/determinant-tests/det-int2x2.dat";
    std::ifstream fin(test_filepath);
    if (!fin.is_open()) {
      std::cout << "error: can't open file: " << test_filepath;
      exit(1); //TODO: replace it by exception
    }
    int n;
    fin >> n;
    std::vector<int> seq(n * n);
    for (int i = 0; i < n * n; i++) {
      fin >> seq[i];
    }
    int answer;
    fin >> answer;
    Matrix<int> matrix(n, n, seq.begin(), seq.end());
    EXPECT_EQ(matrix.RecursiveDet(), answer);
    fin.close();
  }
  //3x3
  {
    std::string test_filepath = GetResourcesPath() +
        "/determinant-tests/det-int3x3.dat";
    std::ifstream fin(test_filepath);
    if (!fin.is_open()) {
      std::cout << "error: can't open file: " << test_filepath;
      exit(1); //TODO: replace it by exception
    }
    int n;
    fin >> n;
    std::vector<int> seq(n * n);
    for (int i = 0; i < n * n; i++) {
      fin >> seq[i];
    }
    int answer;
    fin >> answer;
    Matrix<int> matrix(n, n, seq.begin(), seq.end());
    EXPECT_EQ(matrix.RecursiveDet(), answer);
    fin.close();
  }
  {
    std::string test_filepath = GetResourcesPath() +
        "/determinant-tests/det-int6x6.dat";
    std::ifstream fin(test_filepath);
    if (!fin.is_open()) {
      std::cout << "error: can't open file: " << test_filepath;
      exit(1); //TODO: replace it by exception
    }
    int n;
    fin >> n;
    std::vector<int> seq(n * n);
    for (int i = 0; i < n * n; i++) {
      fin >> seq[i];
    }
    int answer;
    fin >> answer;
    Matrix<int> matrix(n, n, seq.begin(), seq.end());
    EXPECT_EQ(matrix.RecursiveDet(), answer);
    fin.close();
  }
}
TEST(MatrixMethodsTests, ToVectorTest) {
  int m = 5, n = 6;

  std::vector<std::vector<int>> v(m, std::vector<int>(n, 0));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      v[i][j] = i;
  }

  Matrix<int> matrix(m, n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      matrix[i][j] = i;
  }

  std::vector<std::vector<int>> v2 = matrix.ToVector();

  EXPECT_EQ(v, v2);
}