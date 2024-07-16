#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;
using namespace std;

//' Multiply With Carry (MWC)
//'
//' The multiply-with-carry (MWC) method is a method invented by \href{https://en.wikipedia.org/wiki/George_Marsaglia}{George Marsaglia} for generating sequences of random integers based on an initial set of from two to manu thousands of randomly chosent seed values. The main advantages of the MWC mehtod are that it invokes simple computer integer arithmetic and leads to very fast generation of sequences of random numbers with immense periods, ranging from around \eqn{2^{60}} to \eqn{2^{20000000}}.
//'
//' A MWC generator is a special form of a Lehmer Random Number Generator (see \code{\link{lcg_parkmiller}}) \eqn{x_n=bx_{n-1} \mod p} which allows efficient implementation of a prime modulus \eqn{p} much larger than the machine word size.
//'
//' Normal Lehmer generator implementations choose a modulsus close to the machine word size. A MWC generator instead maintains its state it base \eqn{b}, so multiplying by \eqn{b} is done implicitly by shifting one word. The base \eqn{b} is typically chosen to equal the computer's word size, as this makes the arithmetic modulo \eqn{b} trivial. This may vary from \eqn{b=2^8} for a microcontroller to \eqn{b=2^{64}}.
//'
//'The initial seed values are arbitrary,except that they must not all e zero, nor at the maximum permitted values (\eqn{x_0 =b-1 \text{ and } c_0 = a-1}).
//'
//' The \code{mwc()} function implements creates a lag-1 MWC with the seed values. That is:
//'
//' \eqn{x_n = (ax_{n-1} + c_{n-1}) \mod b, c = \lfloor{\frac{ax_{n-1}+c_{n-1}}{b}} \rfloor}
//'
//' For more information, see the \href{https://en.wikipedia.org/wiki/Multiply-with-carry_pseudorandom_number_generator}{Wikipedia page}.
//'
//' @param seed initial starting value
//' @param n number of random numbers desired to be generated
//' @param b by default set to \eqn{2^{32} = 4294967296}
//' @param a by default set to 7
//' @param c by default set to 4
//' @export
//' @examples
//' random_numbers <- mwc(6793,1000)
//' # Plot numbers to see that they are random
//' plot(random_numbers)
//' @export
// [[Rcpp::export]]


NumericVector mwc(int seed, int n, long long b = 4294967296, long long a = 7, long long c = 4){
  NumericVector generated_numbers;
  long long x = seed;

  for(int i = 0; i < n; ++i){
    long long old_x = x;
    x = (a * old_x + c) % b;
    c = floor((a * old_x + c) / b);
    generated_numbers.push_back(x);
  }
  return generated_numbers;
}


// Testing
/*** R
mwc(6793,1000)
*/
