#include "matrix.h"

template<typename T> Matrix<T>::Matrix(): rows_(0), cols_(0), rows_ptr_(nullptr) {}
template<typename T> Matrix<T>::Matrix(int rows, int cols, T val = T{}): rows_(rows), cols_(cols) {
  rows_ptr_ = new Row<T>[rows_];
  for (int i = 0; i < rows_; i++) {
    rows_ptr_[i] = Row<T>(cols_, val);
  }
}
template<typename T> Matrix<T>::Matrix(const Matrix &rhs): rows_(rhs.rows_), cols_(rhs.cols_) {
  rows_ptr_ = new Row<T>[rows_];
  for (int i = 0; i < rows_; i++)
    rows_ptr_[i] = rhs.rows_ptr_[i];
}
template<typename T> Matrix<T>::Matrix(Matrix &&rhs) noexcept: rows_ptr_(rhs.rows_ptr_), rows_(rhs.rows_),
cols_(rhs.cols_) {
rhs.rows_ptr_ = nullptr;
}

template<typename T> Matrix<T>& Matrix<T>::operator=(const Matrix &rhs) {
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
template<typename T> Matrix<T>& Matrix<T>::operator=(Matrix &&rhs) noexcept {
  if (this == &rhs)
    return *this;

  rows_ = rhs.rows_;
  cols_ = rhs.cols_;
  delete[] rows_ptr_;
  rows_ptr_ = rhs.rows_ptr_;
  rhs.rows_ptr_ = nullptr;
  return *this;
}

template<typename T> Matrix<T>::Matrix() {
  delete[] rows_ptr_;
}

template<typename T> Row<T>& Matrix<T>::operator[](int n) {return rows_ptr_[n];}
template<typename T> const Row<T>& Matrix<T>::operator[](int n) const {return rows_ptr_[n];}
template<typename T> bool Matrix<T>::operator==(const Matrix &rhs) const{
  if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++)
    if (rows_ptr_[i] != rhs.rows_ptr_[i])
      return false;

  return true;
}
template<typename T> bool Matrix<T>::operator!=(const Matrix &rhs) const {
  return !(*this == rhs);
}

template<typename T> void Matrix<T>::Print() const {
  std::cout << "Matrix " << rows_ << "x" << cols_ << ":\n\n";
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << rows_ptr_[i][j] << "  ";
    }
    std::cout << std::endl;
  }
}