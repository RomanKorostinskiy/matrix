#include "row.h"

template<typename T> Row<T>::Row(): cols_(0), data_(nullptr) {}
template<typename T> Row<T>::Row(int cols, T val ):cols_(cols) {
  data_ = new T[cols_];
  for (int i = 0; i < cols_; i++) {
    data_[i] = val;
  }
}
template<typename T> Row<T>::Row(const Row &rhs): cols_(rhs.cols_) {
  data_ = new T[cols_];
  std::memcpy(data_, rhs.data_, cols_ * sizeof(T));
}
template<typename T> Row<T>::Row(Row &&rhs) noexcept : data_(rhs.data_),
  cols_(rhs.cols_) {
  rhs.data_ = nullptr;
}

template<typename T> Row<T>& Row<T>::operator=(const Row &rhs) {
  if (this == &rhs)
    return *this;

  cols_ = rhs.cols_;
  delete[] data_;
  data_ = new T[cols_];
  std::memcpy(data_, rhs.data_, rhs.cols_ * sizeof(T));
  return *this;
}
template<typename T> Row<T>& Row<T>::operator=(Row &&rhs) noexcept {
  if (this == &rhs)
    return *this;

  cols_ = rhs.cols_;
  delete[] data_;
  data_ = rhs.data_;
  rhs.data_ = nullptr;
  return *this;
}

template<typename T> Row<T>::~Row() {
  delete[] data_;
}

template<typename T> T& Row<T>::operator[](int n) {return data_[n];}
template<typename T> const T& Row<T>::operator[](int n) const {return data_[n];}
template<typename T> bool Row<T>::operator==(Row const& rhs) const {
  if (cols_ != rhs.cols_) {
    return false;
  }
  for (int i = 0; i < cols_; i++)
    if (data_[i] != rhs.data_[i])
      return false;

  return true;
}
template<typename T> bool Row<T>::operator!=(Row const& rhs) const {
  return !(*this == rhs);
}

template<typename T> void Row<T>::Print() const {
  std::cout << "Row " << cols_ << ":" << std::endl;
  for (int i = 0; i < cols_; i++) {
    std::cout << data_[i] << " ";
  }
  std::cout << std::endl << std::endl;
}