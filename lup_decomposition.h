#pragma once

#include "matrix.h"
#include <vector>
#include <numeric>
#include <cmath>

template <typename T>
std::tuple<Matrix<T>, std::vector<size_t>> LUP_decomposition(Matrix<T> A) {
  size_t n = A.get_num_rows();

  std::vector<size_t> pi(n);

  // pi = [0..n-1]
  std::iota(pi.begin(), pi.end(), 0);

  // k is the current first column
  for(size_t k = 0 ; k < n ; ++k) {
    size_t k_prime = k;
    T p = 0;

    for(size_t i = k ; i < n ; ++i) {
      if(std::greater<T>()(std::abs(A(i,k)),p)) {
        p = std::abs(A(i,k));
        k_prime = i;
      }
    }

    if(p == 0) throw std::invalid_argument("singular matrix");

    std::swap(pi[k], pi[k_prime]);

    for(size_t i = 0 ; i < n ; ++ i)
      std::swap(A(k,i), A(k_prime, i));

    for(size_t i = k + 1 ; i < n ; ++i) {
      A(i,k) = A(i,k)/A(k,k);

      for(size_t j = k+1 ; j < n ; ++j) 
        A(i,j) = A(i,j) - A(i,k)*A(k,j);
    }
  }
  return {A,pi};
}
