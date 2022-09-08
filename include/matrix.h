#pragma once

#include <iostream>
#include "row.h"

template<typename T> class Matrix {
  Row<T> *rows_ptr_;
  int rows_, cols_;

 public:
  Matrix(): rows_(0), cols_(0), rows_ptr_(nullptr) {}
  Matrix(int rows, int cols, T val = T{}): rows_(rows), cols_(cols) {
    rows_ptr_ = new Row<T>[rows_];
    for (int i = 0; i < rows_; i++) {
      rows_ptr_[i] = Row<T>(cols_, val);
    }
  }
  Matrix(const Matrix &rhs): rows_(rhs.rows_), cols_(rhs.cols_) {
    rows_ptr_ = new Row<T>[rows_];
    for (int i = 0; i < rows_; i++)
      rows_ptr_[i] = rhs.rows_ptr_[i];
  }
  Matrix(Matrix &&rhs) noexcept: rows_ptr_(rhs.rows_ptr_), rows_(rhs.rows_),
    cols_(rhs.cols_) {
    rhs.rows_ptr_ = nullptr;
  }

  Matrix& operator=(const Matrix &rhs) {
    if (this == &rhs)
      return *this;

    rows_ = rhs.rows_;
    cols_ = rhs.cols_;
    delete[] rows_ptr_;
    rows_ptr_ = new Row<T>[rows_];
    for (int i = 0; i < rows_; i++)
      rows_ptr_[i] = rhs.rows_ptr_[i];
    return *this;
  }
  Matrix& operator=(Matrix &&rhs) noexcept {
    if (this == &rhs)
      return *this;

    rows_ = rhs.rows_;
    cols_ = rhs.cols_;
    delete[] rows_ptr_;
    rows_ptr_ = rhs.rows_ptr_;
    rhs.rows_ptr_ = nullptr;
    return *this;
  }

  ~Matrix() {
    delete[] rows_ptr_;
  }

  Row<T>& operator[](int n) {return rows_ptr_[n];}
  const Row<T>& operator[](int n) const {return rows_ptr_[n];}
  bool operator==(const Matrix &rhs) const{
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
      return false;
    }
    for (int i = 0; i < rows_; i++)
      if (rows_ptr_[i] != rhs.rows_ptr_[i])
        return false;

    return true;
  }
  bool operator!=(const Matrix &rhs) const {
    return !(*this == rhs);
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