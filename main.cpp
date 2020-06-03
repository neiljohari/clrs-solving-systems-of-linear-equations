#include <iostream>

#include "utils.h"

#include "matrix.h"
#include "lup_solve.h"
#include "lup_decomposition.h"

using namespace std;

Matrix<double> solve(const Matrix<double>& A, const Matrix<double>& b) {
  auto [LU, pi] = LUP_decomposition(A);
  return LUP_solve(LU, LU, pi, b);
}

int main() {
  // Discard a comment line
  string junk;
  getline(cin,junk);

  // Read in number of rows & cols
  unsigned n = 0;
  cin >> n;

  // Prepare matrices to solve Ax=b
  Matrix<double> A(n,n);
  Matrix<double> b(n,1);

  // Read in [A | b]
  for(unsigned i = 0 ; i < n ; ++i) {
    double val = 0;
    for(unsigned j = 0 ; j < n ; ++j) {
      cin >> val;
      A(i,j) = val;
    }

    cin >> val; // read in b
    b(i,0) = val;
  }

  // Solve via LUP decomposition method
  auto res = solve(A,b);

  cout << "Solved! x = [\n" << res << "]\n";

  return 0;
}
