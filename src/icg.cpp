#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

/*
 * Wikipedia: https://en.wikipedia.org/wiki/Inversive_congruential_generator
 */
// [[Rcpp::export]]
NumericVector icg(int q,int a, int c,int seed, int n) {
  NumericVector generated_numbers;
  int number = seed;

  for (int i = 0; i < n; ++i) {
    if (number == 0) {
      number = c;
    } else {
      number = (a * number + c) % q;
    }
    generated_numbers.push_back(number);
  }

  return generated_numbers;
}



// Testing
/*** R
icg(12356,2,3,1,100)
*/



