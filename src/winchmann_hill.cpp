#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

/*
 * Wikipedia: https://en.wikipedia.org/wiki/Wichmann%E2%80%93Hill
 * The Wichmann-Hill random number generator indeed produces pseudorandom numbers that are typically in the range [0, 1).
 *  It generates floating-point numbers rather than discrete integers.
 */

// Utility function
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

// [[Rcpp::export]]
NumericVector winchmann_hill(int seed1,int seed2, int seed3, int n) {

  NumericVector s1 =  lcg(seed1, n);
  NumericVector s2 =  lcg(seed2, n);
  NumericVector s3 =  lcg(seed3, n);

  NumericVector result = ((s1/30269)  + (s2/30307)  + (s3/30323));

  for (int i = 0; i < result.size(); ++i) {
    result[i] = fmod(result[i], 1.0);
  }

  return result;
}
