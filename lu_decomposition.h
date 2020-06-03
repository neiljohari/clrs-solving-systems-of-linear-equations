#pragma once

#include "matrix.h"
#include <vector>

/*
  This function is an implementation of the LU-DECOMPOSITION(A) procedure outlined in CLRS "Introduction to Algorithms". See page 821 of 3rd edition.

  Description: 
    We have a method to solve Ax=b given the LUP decomposition of A (see lup_solve.h). Now we must find a way to quickly compute this LUP decomposition. This method implements the case where P=I_n (i.e. the permutation is absent).

  Runtime Complexity: O(n^3)

  Parameters:
    A = The coefficient matrix in Ax=b

  Output:
    [L, U] as matrices in a tuple
*/
template <typename T>
std::tuple<Matrix<T>, Matrix<T>> LU_decomposition(Matrix<T> A) {
  size_t n = A.get_num_rows();

  // let L and U be new n x n matrices
  Matrix<T> L(n,n);
  Matrix<T> U(n,n);

  // initialize U with 0s below the diagonal
  for(size_t j = 0 ; j < n - 1 ; ++j) {
    for(size_t i = j + 1 ; i < n ; ++i) {
      U(i,j) = 0;
    }
  }

  // initialize L with 1s on the diagonal and 0s above the diagonal
  for(size_t i = 0 ; i < n ; ++i) {
    for(size_t j = i ; j < n ; ++j) {
      L(i,j) = (i==j) ? 1 : 0;
    }
  }

  // We stick to CLRS naming convention, but k can be more aptly called current
  // working column
  for(size_t k = 0 ; k < n ; ++k) { 
    // Determine pivot
    T pivot = U(k,k) = A(k,k);
    
    // Updates L and U using the v and w subparts in the recursive strategy
    for(size_t i = k+1 ; i < n ; ++i) {
      // The L value follows the column below the pivot divided by the pivot
      // v/a_{1,1} from (28.8)
      L(i,k) = A(i,k)/pivot;

      // The U value simply copies the row to the right of the pivot
      // (transpose(w))
      U(k,i) = A(k,i);
    }
    
    // Computes elements of the Schur component
    // The Schur component is A' - v * transpose(W) / a_{1,1}
    for(size_t i = k+1 ; i < n ; ++i){
      for(size_t j = k+1 ; j < n ; ++j) {
        // We do not divide by a_{1,1} since the L values are already divided by
        // the pivot
        A(i,j) = A(i,j) - L(i,k)*U(k,j);
      }
    }
  }


  return {L, U};
}
