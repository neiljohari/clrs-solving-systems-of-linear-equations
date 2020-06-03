#include <iostream>

#include "utils.h"

#include "matrix.h"
#include "lup_solve.h"
#include "lu_decomposition.h"

using namespace std;

void test_lup_solve() {
  cout << "Testing LUP-SOLVE procedure...\n";

  Matrix<double> L(3,3, { 1, 0, 0, 0.2, 1, 0, 0.6, 0.5, 1});

  Matrix<double> U(3,3, { 5, 6, 3, 0, 0.8, -0.6, 0, 0, 2.5});

  // P = { 0 0 1,
  //       1 0 0,
  //       0 1 0 }
  vector<size_t> pi = {2, 0, 1};

  Matrix<double> b(3,1, {3, 7, 8});

  Matrix<double> result = LUP_solve(L, U, pi, b);

  Matrix<double> expected_result(3,1,{-1.4, 2.2, 0.6});

  assert(result == expected_result);

  cout << "PASSED!\n";
}

void test_lu_decomposition() {
  cout << "Testing LU-DECOMPOSITION procedure...\n";

  Matrix<double> A(4,4, {2,3,1,5,6,13,5,19,2,19,10,23,4,10,11,31});

  auto [L, U] = LU_decomposition(A);

  Matrix<double> expected_L(4,4,{1,0,0,0,3,1,0,0,1,4,1,0,2,1,7,1});
  Matrix<double> expected_U(4,4,{2,3,1,5,0,4,2,4,0,0,1,2,0,0,0,3});

  assert(L == expected_L);
  assert(U == expected_U);

  cout << "PASSED!\n";
}

int main() {
  test_lup_solve();
  test_lu_decomposition();
  return 0;
}
