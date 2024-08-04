#include <Rcpp.h>
#include <math.h>

using namespace std;
using namespace Rcpp;

//' Lagged Fibonacci Generator (LFG)
//'
//' A Lagged Fibbonacci Generator (LFG or sometimes LFib) is an example of a pseudorandom number generator. This class of pseudorandom number generator is aimed at being an improvment of the 'standard' linear congruential generator.  These are based on the generalization of the Fibbonacci sequence.
//'
//' The Fibonacci sequence may be described by the recurrence relation:
//'
//' \eqn{S_n = S_{n-1}+S_{n-2}}
//'
//' Hence, the new term is the sum of the last two terms in the sequence This can be generalized by the sequence:
//'
//' [NEED TO CONTINUE]
//'
//' \eqn{S_n \eqiv S_{n-j} \star S_{n-k} \space (\text{mod }m), 0 < j <k}
//'
//' @param int n number of random numbers to generate.
//' @param j \eqn{j} value specified. Note \eqn{0 < j <k}.
//' @param k  \eqn{k} value specified. Note \eqn{0 < j <k}.
//' @param bitsize maximum number of bits got \eqn{m}
//' @examples
//' random_numbers <- lfg(10000)
//' # Plot numbers to see that they are random
//' plot(random_numbers)
//' @export
//[[Rcpp::export]]

NumericVector lfg(int n, int j = 65, int k = 71, int bitsize=32) {

  // ensure that k > j > 0
  if (j <= 0 || k <= 0 || k <= j) {
    stop("Invalid lag values: ensure that 0 < j < k.");
  }

  // initialize the seed vector
  NumericVector fib_series(k);
  fib_series[0] = 0;
  fib_series[1] = 1;

  for (int i = 2; i < k; ++i) {
    fib_series[i] = (fib_series[i - 1] + fib_series[i - 2]);
  }

  // Initialize the output vector
  NumericVector lfg_numbers(n);
  lfg_numbers[0] = fib_series[k-k+1];
  lfg_numbers[1] = fib_series[k-j];
  // Generate the numbers using the LFG algorithm
  for(int i = 2; i < n; ++i) {
   lfg_numbers[i] = fmod(lfg_numbers[i-1] + lfg_numbers[i-2], pow(2,bitsize));
  }

  return lfg_numbers;
}

// Testing
/*** R
plot(
lfg(10000, bitsize=32)
)
*/




