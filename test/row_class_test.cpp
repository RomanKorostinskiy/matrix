#include "gtest/gtest.h"
#include "row.hpp"

using namespace testing;

TEST(RowOperatorsTests, EqualsTest) {
  //Equal
  Row<int> row(5, 0);
  EXPECT_EQ(row, row);

  Row<int> row1(5, 0);
  Row<int> row2(5, 0);
  EXPECT_EQ(row1, row2);

  //Not Equal
  Row<int> row3(5, 0);
  Row<int> row4(6, 0);
  EXPECT_NE(row3, row4);

  Row<int> row5(5, 0);
  Row<int> row6(5, 1);
  EXPECT_NE(row5, row6);
}
TEST(OperatorsTests, SquareBracketsTest) {
  const Row<int> row1(5, 1);
  for (int i = 0; i < 5; i++)
    EXPECT_EQ(row1[i], 1);

  Row<int> row2(5, 1);
  for (int i = 0; i < 5; i++) {
    row2[i] = i;
    EXPECT_EQ(row2[i], i);
  }
}

TEST(RowRAII_Tests, CopyConstructorTest) {
  //Equal
  Row<int> row1(5, 0);
  Row<int> row2 = row1;
  EXPECT_EQ(row1, row2);

  //Not Equal
  Row<int> row3(5, 1);
  Row<int> row4(row2);
  EXPECT_NE(row3, row4);
}
TEST(RowRAII_Tests, CopyAssignmentTest) {
  //Equal
  Row<int> row1(5, 0);
  Row<int> row2(5, 0);
  Row<int> row3;
  Row<int> row4;
  row3 = row1;
  row4 = row2;
  EXPECT_EQ(row3, row4);

  //Not Equal
  Row<int> row5(5, 0);
  Row<int> row6(5, 1);
  Row<int> row7(1, 1);
  Row<int> row8(1, 1);
  row7 = row5;
  row8 = row6;
  EXPECT_NE(row7, row8);
}
TEST(RowRAII_Tests, MoveConstructorTest) {
  //Equal
  Row<int> row1 = Row<int>(5, 0);
  Row<int> row2(Row<int>(5, 0));
  EXPECT_EQ(row1, row2);

  Row<int> row3(std::move(row1));
  Row<int> row4 = std::move(row2);
  EXPECT_EQ(row3, row4);

  //Not Equal
  Row<int> row5 = Row<int>(5, 0);
  Row<int> row6(Row<int>(5, 1));
  EXPECT_NE(row5, row6);

  Row<int> row7(std::move(row5));
  Row<int> row8 = std::move(row6);
  EXPECT_NE(row7, row8);
}
TEST(RowRAII_Tests, MoveAsignmentTest) {
  //Equal
  Row<int> row1(5, 0);
  Row<int> row3;
  Row<int> row4;
  row3 = std::move(row1);
  row4 = Row<int>(5, 0);
  EXPECT_EQ(row3, row4);

  //Not Equal
  Row<int> row5(5, 0);
  Row<int> row7(1, 1);
  Row<int> row8(1, 1);
  row7 = std::move(row5);
  row8 = Row<int> (5, 1);
  EXPECT_NE(row7, row8);
}

TEST(RowRAII_TemplateTest, CopyAssignmentTest) {
  //Equal
  std::shared_ptr<int> ip = std::make_shared<int>(0);
  Row<std::shared_ptr<int>> row1(5, ip);
  Row<std::shared_ptr<int>> row2(5, ip);
  Row<std::shared_ptr<int>> row3;
  Row<std::shared_ptr<int>> row4;
  row3 = row1;
  row4 = row2;
  EXPECT_EQ(row3, row4);

  //Not Equal
  Row<std::shared_ptr<int>> row5(5, std::make_shared<int>(0));
  Row<std::shared_ptr<int>> row6(5, std::make_shared<int>(0));
  Row<std::shared_ptr<int>> row7(1);
  Row<std::shared_ptr<int>> row8(1);
  row7 = row5;
  row8 = row6;
  EXPECT_NE(row7, row8);
}
