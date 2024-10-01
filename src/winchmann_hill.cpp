#include <Rcpp.h>
#include <math.h>
#include "lcg_internal.h"
using namespace Rcpp;

//' Winchman-Hill
//'
//' The Wichmann-Hill random number generator indeed produces pseudorandom numbers that are typically in the range \eqn{\left[0, 1\right)}. It generates floating-point numbers rather than discrete integers.
//'
//' For more information see the \href{https://en.wikipedia.org/wiki/Wichmann%E2%80%93Hill}{Wikipedia Page}
//'
//' @param seed1 Initial seed value.
//' @param seed2 Initial seed value.
//' @param seed3 Initial seed value.
//' @param n Number of random numbers to generate.
//' @examples
//' random_numbers <- winchmann_hill(1234, 4321,5678,1000)
//' # Plot numbers to see that they are random
//' plot(random_numbers)
//' @export
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


/*** R
random_numbers <- winchmann_hill(1234, 4321,5678,1000)
# Plot numbers to see that they are random
plot(random_numbers)
*/
