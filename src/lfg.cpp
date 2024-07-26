#include <Rcpp.h>
#include <vector>
#include <math.h>

using namespace std;
using namespace Rcpp;

// Lagged Fibonacci Generator (LFG)
// [[Rcpp::export]]
NumericVector lfg(int seed, int n) {
  // lags j and k
  int j = 7;
  int k = 8;

  // ensure that k > j > 0
  if (j <= 0 || k <= 0 || k <= j) {
    stop("Invalid lag values: ensure that 0 < j < k.");
  }

  // initialize the seed vector
  //vector<long long> fib_series(seed);
  NumericVector fib_series(seed);
  fib_series[0] = 0;
  fib_series[1] = 1;

  for (int i = 2; i < seed; ++i) {
    fib_series[i] = (fib_series[i - 1] + fib_series[i - 2]);
  }

  // Initialize the output vector
  NumericVector lfg_numbers(n);
  lfg_numbers[0] = fib_series[k-k+1];
  lfg_numbers[1] = fib_series[k-j];
  // Generate the numbers using the LFG algorithm
  for(int i = 2; i < n; ++i) {
   // modulus is 2^32
   lfg_numbers[i] = fmod(lfg_numbers[i-1] + lfg_numbers[i-2], pow(2,32));
  }

  return lfg_numbers;
}

// Testing
/*** R
plot(lfg(13124, 10000))
*/




