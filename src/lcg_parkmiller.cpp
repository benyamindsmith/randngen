#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;
//' Park Miller Generator
//'
//' TODO: Documentation
//'
//' For more information see the \href{https://en.wikipedia.org/wiki/Lehmer_random_number_generator}{Wikipedia page}.
//'
//' @param seed initial starting value
//' @param n the number of random numbers you want to create.
//' @examples
//' random_numbers <- lcg_parkmiller(1234, 1000)
//' # Plot numbers to see that they are random
//' plot(random_numbers)
//' @export
// [[Rcpp::export]]

NumericVector lcg_parkmiller(int seed, int n) {
  NumericVector generated_numbers;
  long long m  = pow(2,31)-1;
  long long a = pow(7,5);
  int number = seed;
  for (int i = 0; i < n; ++i) {
    number = a * number % m;
    generated_numbers.push_back(number);
  }

  return generated_numbers;
}
