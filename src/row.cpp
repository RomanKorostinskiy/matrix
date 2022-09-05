#include "row.h"

template<typename T> Row<T>::Row(int cols, T val): cols_(cols) {
  data_ = new T[cols_];
  for (int i = 0; i < cols_; i++) {
    data_[i] = val;
  }
}
template<typename T> Row<T>::~Row() {
  delete[] data_;
}
template<typename T> void Row<T>::Print() const {
  std::cout << "Row " << cols_ << ":\n\n";
  for (int i = 0; i < cols_; i++) {
    std::cout << data_[i] << "  ";
  }
  std::cout << std::endl;
}