#pragma once

#include <iostream>
#include <cstring>

template<typename T> class RowBuf {
 protected:
  int cols_;
  T* data_;

 protected:
  explicit RowBuf(int cols = 0, T val = T{}): cols_(cols),
      data_((cols_ == 0) ? nullptr : new T[cols]) {
    for (int i = 0; i < cols_; i++)
      data_[i] = T{val};
  }
  RowBuf(const RowBuf &rhs) = delete;
  RowBuf& operator=(const RowBuf &rhs) = delete;
  RowBuf(RowBuf &&rhs) noexcept: cols_(rhs.cols_), data_(rhs.data_){
    rhs.cols_ = 0;
    rhs.data_ = nullptr;
  }
  RowBuf& operator=(RowBuf &&rhs) noexcept {
    std::swap(cols_, rhs.cols_);
    std::swap(data_, rhs.data_);
    return *this;
  }
  ~RowBuf() {
    delete[] data_;
  }
};

template<typename T> class Row: private RowBuf<T> {
  using RowBuf<T>::cols_;
  using RowBuf<T>::data_;

 public:
  Row(int cols = 0, T val = T{}): RowBuf<T>(cols, val) {}
  Row(const Row &rhs): RowBuf<T>(rhs.cols_) {
    for (int i = 0; i < cols_; i++)
      data_[i] = rhs.data_[i];
  }
  Row(Row &&rhs) = default;
  Row& operator=(const Row &rhs) {
    Row tmp(rhs);
    std::swap(*this, tmp);
    return *this;
  }
  Row& operator=(Row &&rhs) = default;
  ~Row() = default;

  T& operator[](int n) {return data_[n];}
  const T& operator[](int n) const {return data_[n];}
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

  void Dump() const {
    std::cout << "Row " << cols_ << ":" << std::endl;
    for (int i = 0; i < cols_; i++) {
      std::cout << data_[i] << " ";
    }
    std::cout << std::endl << std::endl;
  }
};