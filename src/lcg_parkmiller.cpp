#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;
//' Park Miller Generator
//'
//' The Lehmer random number generator[1] (named after D. H. Lehmer), sometimes also referred to as the Park–Miller random number generator (after Stephen K. Park and Keith W. Miller), is a type of linear congruential generator (LCG) that operates in multiplicative group of integers modulo n. The general formula is:\cr\cr
//' \eqn{\displaystyle X_{k+1}=a\cdot X_{k}{\text{ mod } {m}},}\cr\cr
//'where the modulus m is a prime number or a power of a prime number, the multiplier a is an element of high multiplicative order modulo m (e.g., a primitive root modulo n), and the seed \eqn{X_0} is coprime to \eqn{m}.
//'
//' Other names are multiplicative linear congruential generator (MLCG)[2] and multiplicative congruential generator (MCG).
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
