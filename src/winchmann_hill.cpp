#include <Rcpp.h>
#include <math.h>
#include "lcg_internal.h"
using namespace Rcpp;

/*
 * Wikipedia: https://en.wikipedia.org/wiki/Wichmann%E2%80%93Hill
 * The Wichmann-Hill random number generator indeed produces pseudorandom numbers that are typically in the range [0, 1).
 *  It generates floating-point numbers rather than discrete integers.
 */
// [[Rcpp::export]]
NumericVector winchmann_hill(int seed1,int seed2, int seed3, int n) {

  NumericVector s1 =  lcg_internal(seed1, n);
  NumericVector s2 =  lcg_internal(seed2, n);
  NumericVector s3 =  lcg_internal(seed3, n);

  NumericVector result = ((s1/30269)  + (s2/30307)  + (s3/30323));

  for (int i = 0; i < result.size(); ++i) {
    result[i] = fmod(result[i], 1.0);
  }

  return result;
}
