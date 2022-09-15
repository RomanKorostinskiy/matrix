#pragma once

#include <iostream>
#include <exception>
#include "row.hpp"

template<typename T> class MatrixBuf {
 protected:
  int rows_, cols_;
  Row<T>* rows_ptr_;

 protected:
  explicit MatrixBuf(int rows = 0, int cols = 0, T val = T{}): rows_(rows),
      cols_(cols), rows_ptr_((rows_ == 0) ? nullptr : new Row<T>[rows_]) {
    for (int i = 0; i < rows_; i++) {
      rows_ptr_[i] = Row<T>{cols_, val};
    }
  }
  MatrixBuf(const MatrixBuf &rhs) = delete;
  MatrixBuf& operator=(const MatrixBuf &rhs) = delete;
  MatrixBuf(MatrixBuf &&rhs) noexcept: rows_(rhs.rows_), cols_(rhs.cols_),
      rows_ptr_(rhs.rows_ptr_){
    rhs.rows_ = 0;
    rhs.cols_ = 0;
    rhs.rows_ptr_ = nullptr;
  }
  MatrixBuf& operator=(MatrixBuf &&rhs) noexcept {
    std::swap(rows_, rhs.rows_);
    std::swap(cols_, rhs.cols_);
    std::swap(rows_ptr_, rhs.rows_ptr_);
    return *this;
  }
  ~MatrixBuf() {
    delete[] rows_ptr_;
  }
};

template<typename T> class Matrix: private MatrixBuf<T> {
  using MatrixBuf<T>::rows_;
  using MatrixBuf<T>::cols_;
  using MatrixBuf<T>::rows_ptr_;

 public:
  Matrix(int rows = 0, int cols = 0, T val = T{})
      : MatrixBuf<T>(rows, cols, val) {}
  template <typename It> Matrix(int rows, int cols, It start, It fin)
      : MatrixBuf<T>(rows, cols) {
    if (fin - start != rows_ * cols_)
      throw std::range_error(
          "error: wrong conversation from sequence to matrix");
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++, start++)
        rows_ptr_[i][j] = *start;
    }
  }
  Matrix(const Matrix &rhs): MatrixBuf<T>(rhs.rows_, rhs.cols_) {
    for (int i = 0; i < rows_; i++)
      rows_ptr_[i] = rhs.rows_ptr_[i];
  }
  Matrix(Matrix &&rhs) = default;
  Matrix& operator=(const Matrix &rhs) {
    Matrix tmp(rhs);
    std::swap(*this, tmp);
    return *this;
  }
  Matrix& operator=(Matrix &&rhs) = default;
  ~Matrix() = default;

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

  void Dump() const {
    std::cout << "Matrix " << rows_ << "x" << cols_ << ":" << std::endl;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        std::cout << rows_ptr_[i][j] << "  ";
      }
      std::cout << std::endl;
    }
  }
};