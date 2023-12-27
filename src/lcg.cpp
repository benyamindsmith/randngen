#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

// Wikipedia: https://en.wikipedia.org/wiki/Linear_congruential_generator
// [[Rcpp::export]]
NumericVector lcg(int seed, int n) {
  NumericVector generated_numbers;
  // Presetting Parameters as per ZX81
  long long m  = pow(2,16)+1;
  long long a = 75;
  long long c = 74;
  int number = seed;
  for (int i = 0; i < n; ++i) {
    number = (a * number + c)  % m;
    generated_numbers.push_back(number);
  }

  return generated_numbers;
}

/*** R
lcg(123,10)
*/
