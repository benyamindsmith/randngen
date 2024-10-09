#include <Rcpp.h>
#include <math.h>
#include <boost/integer/mod_inverse.hpp>

using namespace Rcpp;
using boost::integer::mod_inverse;

//' Inversive Congruential Generator
//'
//' Inversive congruential generators are a type of non-linear pseudorandom number generator.They use the modular multiplicative inverse (if it exists) to generate the next number in a sequence. The standard formula for an inversive congruential generator, modulo some prime \eqn{q}, is:
//'  \deqn{
//' x_0 = \text{seed}, \quad x_{i+1} = \left\{
//' \begin{array}{ll}
//' (a x_i^{-1} + c) \mod q & \text{if } x_i \neq 0, \\
//' c & \text{if } x_i = 0.
//' \end{array} \right.
//' } where \eqn{x_i^{-1}} represents the modular inverse of \eqn{x_i} modulo \eqn{q}, and \eqn{a} and \eqn{c} are constants.
//'
//' For more information, please see the \href{https://en.wikipedia.org/wiki/Inversive_congruential_generator}{Wikipedia Page}.
//'
//' @param q The modulus (q > 1). This determines the range of possible values in the generated sequence. The output values will be in the range [0, q-1]. A common choice is a large prime number.
//' @param a The multiplier used in the modular inverse step. It must be an integer and should be chosen such that `a` and `q` are coprime (i.e., gcd(a, q) = 1) for the ICG to work correctly.
//' @param c The constant added at each step of the sequence. It is used to ensure the sequence remains pseudo-random. A common choice is to set `c` to 0, but non-zero values of `c` can also be used to shift the sequence.
//' @param seed The initial starting value for the sequence. It must be a non-negative integer and serves as the first value from which the sequence is generated.
//' @param n The number of random numbers to generate in the sequence.
//' @examples
//' # Based off of Wikipedia's example
//' random_numbers <- icg(5,2,3,1,10)
//' # Plot numbers to see that they are random
//' plot(random_numbers)
//' @export
// [[Rcpp::export]]

NumericVector icg(int q,int a, int c,int seed, int n) {
  NumericVector generated_numbers;
  int x = seed;
  generated_numbers.push_back(seed);

  for (int i = 0; i < n; ++i) {
    if (x == 0 ) {
      x = c;
    } else {
      // number needs to be the modular inverses
      // This works!
      x = (a*mod_inverse(x,q) + c) % q;
    }
    generated_numbers.push_back(x);
  }

  return generated_numbers;
}



// Testing
/*** R
 random_numbers <- icg(5,2,3,1,10)
# Plot numbers to see that they are random
plot(random_numbers)
*/



