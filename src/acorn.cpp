#include <Rcpp.h>
using namespace Rcpp;
//' ACORN Random Number Generator
//'
//' Implements the Additive Congruential Random Number (ACORN) generator,
//' a high-quality pseudorandom number generator based on additive lagged
//' Fibonacci sequences. The generator uses the recurrence relation:
//' Y[i] = (Y[i-1] + Y[i-2] + ... + Y[i-k-1]) mod M
//'
//' @param seed Initial seed value for the generator. Must satisfy 0 < seed < M.
//'   All internal states are initialized to this seed value.
//' @param n Number of random values to generate. Must be non-negative.
//' @param k Order of the generator (default = 1). Higher orders generally provide
//'   better statistical properties. The original ACORN algorithm recommends k = 10
//'   for production use. Must be >= 1.
//' @param M Modulus for the generator (default = 2^30 = 1073741824). Must be a
//'   power of two for efficient computation. The default provides approximately
//'   30 bits of precision.
//'
//' @return A numeric vector of length \code{n} containing pseudo-random uniform
//'   values in the interval [0, 1).
//'
//' @details
//' The ACORN generator maintains a state vector of k+1 previous values and
//' generates new values by summing all previous values modulo M. This additive
//' structure provides good statistical properties and a long period.
//'
//' Key properties:
//' \itemize{
//'   \item Period length increases with order k
//'   \item k = 10 is recommended for general use (balances quality and speed)
//'   \item M must be a power of 2 for efficient modulo operations
//'   \item All generated values are in [0, 1) with resolution 1/M
//' }
//'
//' @section Performance:
//' Computational cost increases linearly with k. For k = 1, the generator is
//' very fast but has limited statistical quality. For k = 10, it provides
//' excellent quality at moderate computational cost.
//'
//' @section References:
//' Wikramaratna, R. S. (1989). ACORN - A new method for generating sequences of
//' uniformly distributed pseudo-random numbers. Journal of Computational Physics,
//' 83(1), 16-31.
//'
//' @examples
//' \dontrun{
//' # Generate 1000 random numbers with default settings (k=1)
//' rng1 <- acorn(seed = 12345, n = 1000)
//'
//' # Use recommended order k=10 for better quality
//' rng10 <- acorn(seed = 12345, n = 1000, k = 10)
//'
//' # Custom modulus (must be power of 2)
//' rng_custom <- acorn(seed = 54321, n = 500, k = 5, M = 2^20)
//'
//' # Verify uniform distribution
//' hist(rng10, breaks = 50, main = "ACORN k=10")
//' }
//'
//' @export
// [[Rcpp::export]]

NumericVector acorn(long long seed, int n, int k = 1, long long M = 1073741824) {
  if (n < 0)
    stop("n must be >= 0");
  if (k < 1)
    stop("k must be >= 1");
  if (seed <= 0 || seed >= M)
    stop("seed must satisfy 0 < seed < M");
  if ((M & (M - 1LL)) != 0)
    stop("M must be a power of two");

  NumericVector generated_numbers(n);

  // Initialize state vector Y with seed values
  std::vector<long long> Y(k + 1);
  for (int i = 0; i <= k; ++i) {
    Y[i] = seed;
  }

  double invM = 1.0 / (double)M;

  for (int i = 0; i < n; ++i) {
    // Calculate new value: sum of all k+1 previous values
    long long sum = 0;
    for (int j = 0; j <= k; ++j) {
      sum += Y[j];
    }
    long long y_new = sum & (M - 1LL);  // fast mod 2^p

    generated_numbers[i] = y_new * invM;

    // Shift state: move everything left and add new value at end
    for (int j = 0; j < k; ++j) {
      Y[j] = Y[j + 1];
    }
    Y[k] = y_new;
  }

  return generated_numbers;
}

/*** R
#Order 12 (ACORN standard)
plot(acorn(12345, 10000, 12, 2^60))
***/
