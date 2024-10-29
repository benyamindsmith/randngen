#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;
//' Linear Congruential Generator
//'
//'A linear congruential generator (LCG) is an algorithm that yields a sequence of pseudo-randomized numbers calculated with a discontinuous piecewise linear equation. The method represents one of the oldest and best-known pseudorandom number generator algorithms. The theory behind them is relatively easy to understand, and they are easily implemented and fast, especially on computer hardware which can provide modular arithmetic by storage-bit truncation.
//'
//'
//' The generator is defined by the recurrence relation:
//' \deqn{X_{n+1} = (aX + c) \text{ mod } m}
//' Where \eqn{X} is the sequence of pseudo-random values and
//'
//' - \eqn{m, 0 < m} - the "modulus"
//'
//' - \eqn{a, 0 < a < m} - the "multiplier"
//'
//' - \eqn{c, 0 \le c < m} - the "increment"
//'
//' - \eqn{X_0, 0 \le X_0 < m} - the "seed" or "start value"
//'
//' For more information see the \href{https://en.wikipedia.org/wiki/Linear_congruential_generator}{Wikipedia page}.
//'
//' @param seed initial starting value
//' @param n the number of random numbers you want to create.
//' @param m modulus argument. By default, \eqn{m = 2^{16}  + 1} (follows ZX81 configuration)
//' @param a multiplier argument. By default, \eqn{a = 75} (follows ZX81 configuration)
//' @param c increment argument By default, \eqn{c = 74} (follows ZX81 configuration)
//' @examples
//' random_numbers <- lcg(1234, 1000)
//' # Plot numbers to see that they are random
//' plot(random_numbers)
//' @export
// [[Rcpp::export]]

NumericVector lcg(int seed, int n,  long long m  = 65537,  long long a = 75,   long long c = 74) {
  NumericVector generated_numbers;
  // Presetting Parameters as per ZX81
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
