#include "matrix.h"

void TestCopyAssignmentLeaks() {
  Row<int> row1(5, 0);
  Row<int> row2(5, 1);

  Row<int> row3(1, 1);
  Row<int> row4(1,1);
  row3 = row1;
  row4 = row2;

  row1.Print(); row2.Print(); row3.Print(); row4.Print();
}

void TestCopyConstructorLeaks() {
  Row<int> row1(5, 0);
  Row<int> row2 = row1;

//Not Equal
  Row<int> row3(5, 1);
  Row<int> row4(row2);

  row1.Print(); row2.Print(); row3.Print(); row4.Print();
}

int main() {
  int rows, cols, val;
  std::cin >> rows >> cols >> val;

  Matrix<int> m(rows, cols, val);
  m.Print();

  TestCopyAssignmentLeaks();
  TestCopyConstructorLeaks();

  return 0;
}