#include <Rcpp.h>
using namespace Rcpp;

//' Xorshift Random Number Generators
//'
//' Xorshift random number generators, also called shift-register generators, are a class of pseudorandom number generators that were invented by George Marsaglia.They are a subset of linear-feedback shift registers (LFSRs) which allow a particularly efficient implementation in software without the excessive use of sparse polynomials. They generate the next number in their sequence by repeatedly taking the exclusive or of a number with a bit-shifted version of itself. This makes execution extremely efficient on modern computer architectures, but it does not benefit efficiency in a hardware implementation. Like all LFSRs, the parameters have to be chosen very carefully in order to achieve a long period.
//'
//' For execution in software, xorshift generators are among the fastest PRNGs, requiring very small code and state. However, they do not pass every statistical test without further refinement. This weakness is amended by combining them with a non-linear function, as described in the original paper. Because plain xorshift generators (without a non-linear step) fail some statistical tests, they have been accused of being unreliable.
//'
//' For more information, check out the \href{https://en.wikipedia.org/wiki/Xorshift}{Wikipedia Page}, \href{George Marsaglia's paper}{https://www.jstatsoft.org/article/view/v008i14} and \href{this StackOverflow post}{https://stackoverflow.com/questions/71522815/why-does-the-xorshift-random-number-generator-always-seem-to-use-these-specific}
//' @name xorshift
//' @param seed Integer-like scalar used to initialize the internal state for
//'   \code{xorshift_32()} (32-bit variant) and \code{xorshift_64()} (64-bit variant).
//'   Different seeds produce different sequences. A seed of 0 is permitted for the
//'   32- and 64-bit variants, but may yield a degenerate sequence depending on platform
//'   integer behavior.
//'
//' @param seed1,seed2,seed3,seed4 Integer-like scalars used to initialize the four-word
//'   internal state for \code{xorshift_128()}. The state must not be all zeros; if all
//'   four seeds are 0, the function errors.
//'
//' @param n Integer scalar. Number of pseudorandom values to generate. Must be
//'   non-negative.
//'
//' @return A numeric vector of length \code{n} containing the generated values.
//'   Values are returned as type \code{numeric} (double) because that is R's default
//'   numeric type.
//'
//' @details
//' These functions implement classic xorshift generators using bitwise XOR and shifts.
//' They are intended for speed and reproducibility, not cryptographic security.
//'
//' @seealso \href{https://en.wikipedia.org/wiki/Xorshift}{Xorshift on Wikipedia}
//' @examples
//' xorshift_32(seed = 51966, n = 1000)
//' xorshift_64(seed = 51966, n = 1000)
//' xorshift_128(123456789, 362436069, 521288629, 88675123, n = 1000)
//' @export
// [[Rcpp::export]]

 NumericVector xorshift_32(long seed, int n){
   NumericVector generated_numbers;
   long x = seed;

   for(int i=0; i < n; i++){
     x ^= x << 13;
     x ^= x >> 17;
     x ^= x << 5;

     generated_numbers.push_back(x);
   }
   return generated_numbers;
 }


//' @rdname xorshift
//' @export
// [[Rcpp::export]]

 NumericVector xorshift_64(long long seed, int n){
   NumericVector generated_numbers;
   long long x = seed;

   for(int i=0; i < n; i++){
     x ^= x << 13;
     x ^= x >> 7;
     x ^= x << 17;

     generated_numbers.push_back(x);
   }
   return generated_numbers;
 }

//' @rdname xorshift
//' @export
// [[Rcpp::export]]
NumericVector xorshift_128(long seed1, long seed2, long seed3, long seed4, int n) {
  NumericVector generated_numbers;

  // Make sure no all-zero state
  if (seed1 == 0 && seed2 == 0 && seed3 == 0 && seed4 == 0) {
    stop("All seeds cannot be zero.");
  }

  long x[4] = {seed1, seed2, seed3, seed4};

  for (int i = 0; i < n; i++) {
    long t = x[3];
    long s = x[0];
    x[3] = x[2];
    x[2] = x[1];
    x[1] = s;

    t ^= t << 11;
    t ^= t >> 8;
    x[0] = t ^ s ^ (s >> 19);

    // Store as double (R uses double for numerics)
    generated_numbers.push_back(x[0]);
  }

  return generated_numbers;
}

/*** R
xorshift_32(seed = 51966, n = 1000)|>
  plot(main = "Xorshift 32")

xorshift_64(seed = 51966, n = 1000)|>
  plot(main = "Xorshift 64")

xorshift_128(123456789, 362436069, 521288629, 88675123, n = 1000)|>
  plot(main = "Xorshift 128")
*/
