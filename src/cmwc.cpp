#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;
using namespace std;

//' Complementary Multiply-with-Carry Generator
//'
//' Generates a sequence of pseudo-random numbers using a multiply-with-carry-style
//' recurrence.
//'
//' The generator updates the state using
//' \deqn{x_i = (a x_{i-1} + c) \bmod b}
//' where \eqn{b = 2^{bitsize}}. The carry is updated as
//' \deqn{c = \left\lfloor (a x_{i-1} + c) / b \right\rfloor}
//'
//' @param seed Initial seed value for the generator.
//' @param n Number of pseudo-random values to generate.
//' @param r Lag parameter for a complementary multiply-with-carry generator.
//'   Currently unused in this implementationde
//' @param bitsize Number of bits used to define the base \eqn{b = 2^{bitsize}}.
//'   Defaults to `32`.
//' @param a Multiplier used in the recurrence. Defaults to `7`.
//' @param c Initial carry value. Defaults to `4`.
//'
//' @return A numeric vector of length `n` containing the generated pseudo-random values.
//'
//' @details
//' This implementation uses a multiply-with-carry recurrence. Although the function
//' is named `cmwc`, the current implementation does not use the lag parameter `r`
//' and does not apply the complementary transformation commonly used in full CMWC
//' generators.
//'
//' @references
//' Wikipedia: Multiply-with-carry pseudorandom number generator.
//' \url{https://en.wikipedia.org/wiki/Multiply-with-carry_pseudorandom_number_generator#Complementary-multiply-withcarry_generators}
//'
//' @examples
//' cmwc(seed = 123, n = 10, r = 5)
//' @export
// [[Rcpp::export]]
 
NumericVector cmwc(long long seed, int n, int r, int bitsize=32, int a=7, int c=4){
  NumericVector generated_numbers;
  long long x = seed;
  long long b = pow(2,bitsize);

  for(int i = 0; i < n; ++i){
    long long old_x = x;
    x = (a * old_x + c) % b;
    c = (a * old_x + c) / b;
    generated_numbers.push_back(x);
  }
  return generated_numbers;
}


// Testing
/*** R
cmwc(6793,1000, 1)|>plot()
*/



