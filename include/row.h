#pragma once

#include <iostream>
#include <cstring>

template<typename T> class Row {
  T *data_;
  int cols_;

 public:
  Row(): cols_(0), data_(nullptr) {}
  Row(int cols, T val = T{}):cols_(cols) {
    data_ = new T[cols_];
    for (int i = 0; i < cols_; i++) {
      data_[i] = val;
    }
  }
  Row(const Row &rhs): cols_(rhs.cols_) {
    data_ = new T[cols_];
    std::memcpy(data_, rhs.data_, cols_ * sizeof(T));
  }
  Row(Row &&rhs) noexcept : data_(rhs.data_), cols_(rhs.cols_) { //TODO: test this
    rhs.data_ = nullptr;
  }

  Row& operator=(const Row &rhs) {
    if (this == &rhs)
      return *this;

    cols_ = rhs.cols_;
    delete[] data_;
    data_ = new T[cols_];
    std::memcpy(data_, rhs.data_, rhs.cols_ * sizeof(T));
    return *this;
  }
  Row& operator=(Row &&rhs) noexcept { //TODO: test this
    if (this == &rhs)
      return *this;

    cols_ = rhs.cols_;
    delete[] data_;
    data_ = rhs.data_;
    rhs.data_ = nullptr;
    return *this;
  }

  bool operator==(Row const& rhs) const {
    if (cols_ != rhs.cols_) {
      return false;
    }
    for (int i = 0; i < cols_; i++)
      if (data_[i] != rhs.data_[i])
        return false;

    return true;
  }
  bool operator!=(Row const& rhs) const {
    return !(*this == rhs);
  }

  ~Row() {
    delete[] data_;
  }

  T& operator[](int n) {return data_[n];}
  const T& operator[](int n) const {return data_[n];}

  void Print() const {
    std::cout << "Row " << cols_ << ":" << std::endl;
    for (int i = 0; i < cols_; i++) {
      std::cout << data_[i] << " ";
    }
    std::cout << std::endl << std::endl;
  }
};