#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;
using namespace std;

/*
 * Wikipedia: https://en.wikipedia.org/wiki/Multiply-with-carry_pseudorandom_number_generator#Complementary-multiply-with-carry_generators
 * NEEDS WORK
 */
// [[Rcpp::export]]


NumericVector cmwc(int seed, int n){
  NumericVector generated_numbers;
  long long x = seed;
  long long b = pow(2,32);
  long long a = 7;
  long long c = 4;

  for(int i = 0; i < n; ++i){
    long long old_x = x;
    x = (a * old_x + c) % b;
    c = (a * old_x + c) / b;
    generated_numbers.push_back(x);
  }
  return 0;
}


// Testing
/*** R
cmwc(6793,1000)
*/



