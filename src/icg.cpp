#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

//' Inversive Congruential Generator
//'
//' Inversive congruential generators are a type of non-linear congregational pseudorandom number generator which use the modular multiplicative inverse (if it exists) to generate the next number in a sequence. \br\br The standard formula for an inversive congruential generator, modulo some prime \eqn{q} is: \br \eqn{x_0 = \text{seed}, \quad x_{i+1} = \left\{ \begin{array}{ll} (a x_i^{-1} + c) \mod q & \text{if } x_i \neq 0, \\ c & \text{if } x_i = 0. \end{array} \right}
//'
//' For more information, please see the \href{https://en.wikipedia.org/wiki/Inversive_congruential_generator}{Wikipedia Page}.
//'
//' @param q TODO
//' @param a TODO
//' @param c TODO
//' @param seed TODO
//' @param n
//'
// [[Rcpp::export]]
NumericVector icg(int q,int a, int c,int seed, int n) {
  NumericVector generated_numbers;
  int number = seed;

  for (int i = 0; i < n; ++i) {
    if (number == 0) {
      number = c;
    } else {
      // number needs to be the modular inverse
      number = (a * number + c) % q;
    }
    generated_numbers.push_back(number);
  }

  return generated_numbers;
}



// Testing
/*** R
icg(5,2,3,1,10)
*/



