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

  int rows() const { return rows_; }
  int cols() const { return cols_; }
  Matrix& DeleteRow(int row) & {
    int offset_row = 0;
    Matrix<T> tmp(rows_ - 1, cols_);
    for (int i = 0; i < rows_ - 1; i++) {
      if (i == row)
        offset_row = 1;
      for (int j = 0; j < cols_; j++)
        tmp[i][j] = rows_ptr_[i + offset_row][j];
    }
    *this = tmp;
    return *this;
  }
  Matrix& DeleteColumn(int col) & {
    int offset_col = 0;
    Matrix<T> tmp(rows_, cols_ - 1);
    for (int i = 0; i < rows_; i++) {
      offset_col = 0;
      for (int j = 0; j < cols_ - 1; j++) {
        if (j == col)
          offset_col = 1;
        tmp[i][j] = rows_ptr_[i][j + offset_col];
      }
    }
    *this = tmp;
    return *this;
  }
  Matrix& DeleteRowColumn(int row, int col) & {
    int offset_col = 0;
    int offset_row = 0;
    Matrix<T> tmp(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_ - 1; i++) {
      offset_col = 0;
      if (i == row)
        offset_row = 1;
      for (int j = 0; j < cols_ - 1; j++) {
        if (j == col)
          offset_col = 1;
        tmp[i][j] = rows_ptr_[i + offset_row][j + offset_col];
      }
    }
    *this = tmp;
    return *this;
  }
  T RecursiveDet() const {  //TODO: optimize and test this function
    if (rows_ != cols_)
      throw std::domain_error(
          "error: can't calculate the determinant of a non-square matrix");
    int current_iter = this->rows();
    T det = 0;
    if (current_iter == 1) {
      return rows_ptr_[0][0];
    }
    for (int i = 0; i < current_iter; i++) {
      int sign = 1 - 2 * (i % 2);
      Matrix<T> tmp = *this;
      tmp.DeleteRowColumn(0, i);
      det += sign * rows_ptr_[0][i] * tmp.RecursiveDet();
    }
    return det;
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