#pragma once

#include <iostream>
#include <vector>

#include "utils.h"

template <typename T> class Matrix {
public:
  Matrix(size_t rows, size_t cols)
      : num_rows(rows), num_cols(cols), data(rows * cols) {}

  Matrix(size_t rows, size_t cols, const std::vector<T> &data)
      : num_rows(rows), num_cols(cols), data(data) {}

  double &operator()(size_t i, size_t j) {
    assert(i >= 0 && i < num_rows);
    assert(j >= 0 && j < num_cols);
    return data[i * num_cols + j];
  };

  double operator()(size_t i, size_t j) const {
    assert(i >= 0 && i < num_rows);
    assert(j >= 0 && j < num_cols);
    return data[i * num_cols + j];
  };


  // Properly does comparisons between matrices of floating points
  bool operator==(const Matrix<T>& rhs) const {
    return num_rows == rhs.num_rows && num_cols == rhs.num_cols &&
      std::equal(data.begin(), data.end(), rhs.data.begin(),
          AlmostEqualsComparator<T>());
  }

  size_t get_num_rows() const {
    return num_rows;
  }

  size_t get_num_cols() const {
    return num_cols;
  }

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& mat);

private:
  size_t num_rows;
  size_t num_cols;
  std::vector<T> data;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
    for(unsigned i = 0 ; i < mat.get_num_rows() ; ++i) {
      for(unsigned j = 0 ; j < mat.get_num_cols() ; ++j) {
        os << mat(i,j) << ' ';
      }
      os << '\n';
    }
    return os;
}


