#include <iostream>
struct T {

};

template<typename T> class Matrix {
  T **data_;
  int rows_, cols_;

 public:
  Matrix(int rows, int cols, T val = T{});
  ~Matrix();
  void Print() const;
};