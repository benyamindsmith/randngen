#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

//' Fibbonacci Linear Feedback Shift Register
//'
//' For more information, check out the \href{https://en.wikipedia.org/wiki/Linear-feedback_shift_register}{Wikipedia Page}.
// [[Rcpp::export]]
NumericVector lfsr_fib(int seed, int n, int bitsize) {
  NumericVector generated_numbers;
  int x = seed;

  for(int i=0; i < n; i++){
    // NEED TO ADD CODE
  }
  return generated_numbers;
}


//' Galois Linear Feedback Shift Register
//'
//' For more information, check out the \href{https://en.wikipedia.org/wiki/Linear-feedback_shift_register}{Wikipedia Page}.
// [[Rcpp::export]]

NumericVector lfsr_galois(int seed, int n, int bitsize){
  NumericVector generated_numbers;
  int x = seed;

  for(int i=0; i < n; i++){

  }
  return generated_numbers;
}

//' Xorshift Linear Feedback Shift Register
//'
//' For more information, check out the \href{https://en.wikipedia.org/wiki/Linear-feedback_shift_register}{Wikipedia Page}.
// [[Rcpp::export]]

NumericVector lfsr_xorshift(int seed, int n, int bitsize){
  NumericVector generated_numbers;
  int x = seed;

  for(int i=0; i < n; i++){

  }
  return generated_numbers;
}

// Testing
/*** R
lfsr_fib()
*/
