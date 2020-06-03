#pragma once

#include "matrix.h"
#include <vector>
#include <numeric>
#include <cmath>

/*
  This function is an implementation of the LUP-DECOMPOSITION(A) procedure
  outlined in CLRS "Introduction to Algorithms". See page 824 of 3rd edition.

  Description:
    In LU-DECOMPOSITION(A), we run the risk of dividing by 0 because we don't
    check our pivots carefully. Additionally, if smaller numbers are higher rows,
    then we will have numerical instability due to roundoff errors.
    This method uses the idea of permutation matrices to swap rows to ensure a
    non-zero largest pivot is chosen.

  Runtime Complexity: O(n^3), thus the swapping incurs at most a constant cost

  Parameters:
    A = The coefficient matrix in Ax=b

  Output:
    [LU, pi] as matrices in a tuple. LU contains the upper & lower triangular
    matrices at once. The algorithm operates in-place on a copy of A.
*/

template <typename T>
std::tuple<Matrix<T>, std::vector<size_t>> LUP_decomposition(Matrix<T> A) {
  size_t n = A.get_num_rows();

  std::vector<size_t> pi(n);

  // pi = [0..n-1]
  std::iota(pi.begin(), pi.end(), 0);

  // k is the current first column
  for(size_t k = 0 ; k < n ; ++k) {
    // k_prime is a potential swap row
    size_t k_prime = k;
    // p tracks the largest pivot value (0 indicates no non-zero col was found)
    T p = 0;

    for(size_t i = k ; i < n ; ++i) {
      if(std::greater<T>()(std::abs(A(i,k)),p)) {
        p = std::abs(A(i,k));
        k_prime = i;
      }
    }

    if(p == 0) throw std::invalid_argument("singular matrix");

    // exchance rows
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
