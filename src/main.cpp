#include "matrix.h"

int main() {
  int rows, cols, val;
  std::cin >> rows >> cols >> val;

  Matrix<int> m(rows, cols, val);

  m.Print();

  return 0;
}