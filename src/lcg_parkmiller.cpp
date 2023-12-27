#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector lcg_parkmiller(int seed, int n) {
  NumericVector generated_numbers;
  long long m  = pow(2,31)-1;
  long long a = pow(7,5);
  int number = seed;
  for (int i = 0; i < n; ++i) {
    number = a * number % m;
    generated_numbers.push_back(number);
  }

  return generated_numbers;
}
