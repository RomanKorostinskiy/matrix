#include "matrix.h"

template<typename T> Matrix<T>::Matrix(int rows, int cols, T val): rows_(rows), cols_(cols) {
  data_ = new T*[rows_];
  for (int i = 0; i < rows_; i++) {
    data_[i] = new T[cols_];
    for (int j = 0; j < cols_; j++) {
      data_[i][j] = val;
    }
  }
}
template<typename T> Matrix<T>::~Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] data_[i];
  }
  delete[] data_;
}
template<typename T> void Matrix<T>::Print() const {
  std::cout << "Matrix " << rows_ << "x" << cols_ << ":\n\n";
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << data_[i][j] << "  ";
    }
    std::cout << std::endl;
  }
}