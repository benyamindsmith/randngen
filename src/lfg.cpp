#include <Rcpp.h>
#include <math.h>
using namespace std;
using namespace Rcpp;

// Wikipedia: https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator
// A Multiplicative Lagged Fibbonacci Generator
// [[Rcpp::export]]

NumericVector lfg(int seed, int n) {
  long long j = 7;
  long long k = 8;
  NumericVector fib_series;
  NumericVector generated_numbers;

  fib_series.push_back(0);
  fib_series.push_back(1);
  for (int i = 2; i < seed; ++i) {
    long long fib_number = fib_series[i- 1] + fib_series[i - 2];
    fib_series.push_back(fib_number);
  }

  // Right now just generated numbers.
  for(int i = 0; i<n; ++i){
     long long lfg_number = fib_series[i-j]*fib_series[i-k];
     generated_numbers.push_back(lfg_number);

  }

  return generated_numbers;
}


// Testing
/*** R
lfg(6793,10)
*/



