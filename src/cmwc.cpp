#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;
using namespace std;

//' Complementary Multiply with Carry Generator
//'
//'
/*
 * Wikipedia: https://en.wikipedia.org/wiki/Multiply-with-carry_pseudorandom_number_generator#Complementary-multiply-with-carry_generators
 * NEEDS WORK
 */
// [[Rcpp::export]]


// CODE NEEDS TO BE FIXED
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



