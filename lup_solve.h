#pragma once

#include "matrix.h"
#include <vector>

/* 
  This function is an implementation of the LUP-SOLVE(L, U, pi, b) procedure
  outlined in CLRS "Introduction to Algorithms". See page 815 of 3rd edition.

  Description:
    Given the LUP decomposition of some matrix A, we can solve for x in Ax = b
    by LUP solve.

  Runtime Complexity: O(n^2)

  Parameters:
    L = The unit lower-triangular decomposition of A
    U = The unit upper-triangular decomposition of A
    p = The permutation matrix represented in array notation (denoted as pi in
        the text). For i = 0, 1, 2,...,n we say the row i of the permutation
        matrix is a 1, while all other entries in that row are 0.
  
  Output:
    The solution vector that satisfies Ax = b
*/
template <typename T>
Matrix<T> LUP_solve(const Matrix<T>& L, const Matrix<T>& U, const std::vector<size_t>& pi, const Matrix<T>& b) {
  assert(b.get_num_cols() == 1);

  size_t n = L.get_num_rows();

  // let x, y be new vectors of length n
  Matrix<T> x(n, 1);
  Matrix<T> y(n, 1);

  // Forward substitution [ O(n^2) ]
  for(size_t i = 0 ; i < n ; ++i) {
   // y_i = b_pi[i] - \sum_1^{i-1} l_{i,j} * y_j

   T sum = 0;
   for(size_t j = 0 ; j < i ; ++j) {
    sum += L(i,j)*y(j,0);
   }

   y(i,0) = b(pi[i],0) - sum;
  }


  // Back substitution [ O(n^2) ]
  // note on size_t decrement loop: this starts at n-1
  //  https://stackoverflow.com/questions/3623263/reverse-iteration-with-an-size_t-loop-variable
  for(size_t i = n; i-- > 0;) {
    // x_i = (y_i - \sum_{i+1}^n u_{i,j} * x_j)/u_{i,i}

    T sum = 0;
    for(size_t j = i+1 ; j < n ; ++j) {
      sum += U(i,j)*x(j,0);
    }
    x(i,0) = (y(i,0) - sum)/U(i,i);
  }

  return x;
}


