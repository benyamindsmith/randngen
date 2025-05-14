#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

// Pull in RDTSC intrinsic
#if defined(__GNUC__) || defined(__clang__)
#include <x86intrin.h>
#elif defined(_MSC_VER)
#include <intrin.h>
#pragma intrinsic(__rdtsc)
#else
#error "RDTSC not supported on this compiler"
#endif

// Helper to read the timestamp counter
static inline uint64_t get_tsc() {
  return __rdtsc();
}


//' TempleOS Linear Congruential Generator (LCG)
//'
//' Generates `n` pseudo-random values using the TempleOS constants, with an initial seed taken from the CPU timestamp counter. This code is inspired from the Linear Congruential Generator Specified in the TempleOS source code. To see the source code in TempleOS, see \href{https://tinkeros.github.io/WbTempleOS/Kernel/KMathB.html#l77}{here}.
//'
//' \code{lcg_tos} differs from \code{lcg} as the parameters are preconfigured and the random seed comes from the CPU timestamp. It is possible to configure \code{lcg_tos} with \code{lcg}, however this is ready to use preconfigured function that only requires the user to specify the number of random numbers they wish to generate.
//'
//' @param n Number of random numbers to generate (default 1).
//' @return A NumericVector of length `n`. Each value is the 64-bit state coerced to double.
//' @examples
//' random_numbers <- lcg_tos(10000)
//' # Plot numbers to see that they are random
//' plot(random_numbers)
//' @seealso \code{\link{lcg}}
//' @export
// [[Rcpp::export]]
 NumericVector lcg_tos(int n = 1) {
   // initial seed from TSC
   uint64_t x = get_tsc();
   long long a = 6364136223846793005;
   long long c = 1442695040888963407;
   NumericVector generated_numbers;
   for (int i = 0; i < n; ++i) {
     x = a * x + c;    // 64-bit overflow == mod 2^64
     generated_numbers.push_back(double(x));
   }
   return generated_numbers;
 }


/*** R
lcg_tos(10000) |> plot()
*/

