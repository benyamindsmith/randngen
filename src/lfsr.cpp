#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

//' Linear Feedback Shift Register
//'
//' For more information, check out the \href{https://en.wikipedia.org/wiki/Linear-feedback_shift_register}{Wikipedia Page}.
// [[Rcpp::export]]
NumericVector lfsr_fib(int seed, int n) {
  return 0;
}

NumericVector lfsr_galois(int seed, int n){
  return 0;
}

NumericVector lfsr_xorshift(int seed, int n){
  return 0;
}

// Testing
/*** R
lfsr()
*/
