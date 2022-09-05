#pragma once

#include <iostream>
#include "row.h"

template<typename T> class Matrix {
  Row<T> *rows_ptr_;
  int rows_, cols_;

 public:
  Matrix(int rows, int cols, T val): rows_(rows), cols_(cols) {
    rows_ptr_ = new Row<T>[rows_];
    for (int i = 0; i < rows_; i++) {
      rows_ptr_[i] = Row<T>(cols_, val);
    }
  }
  ~Matrix() {
    delete[] rows_ptr_;
  }

  void Print() const {
    std::cout << "Matrix " << rows_ << "x" << cols_ << ":\n\n";
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        std::cout << rows_ptr_[i][j] << "  ";
      }
      std::cout << std::endl;
    }
  }
};