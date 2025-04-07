#include <Rcpp.h>
#include <math.h>

using namespace std;
using namespace Rcpp;

//' Lagged Fibonacci Generator (LFG)
//'
//' A Lagged Fibbonacci Generator (LFG or sometimes LFib) is an example of a pseudorandom number generator. This class of pseudorandom number generator is aimed at being an improvment of the 'standard' linear congruential generator.  These are based on the generalization of the Fibbonacci sequence.\cr\cr
//' The Fibonacci sequence may be described by the recurrence relation:\cr\cr
//' \eqn{S_n = S_{n-1}+S_{n-2}}\cr\cr
//' Hence, the new term is the sum of the last two terms in the sequence This can be generalized by the sequence:\cr\cr
//' \eqn{S_n \eqiv S_{n-j} \star S_{n-k} \space (\text{mod }m), 0 < j <k}\cr\cr
//' In which case, the new term is some combination of any two previous terms. m is usually a power of 2 (m = 2M), often 232 or 264. The  \star operator denotes a general binary operation. This may be either addition, subtraction, multiplication, or the bitwise exclusive-or operator (XOR). In this package, the \star operator denotes addition.The theory of this type of generator is rather complex, and it may not be sufficient simply to choose random values for j and k. These generators also tend to be very sensitive to initialisation.
//'
//' For more information, see the \href{https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator}{Wikipedia page}.
//'
//' @param n Number of random numbers to generate.
//' @param j Lag parameter j (0 < j < k).
//' @param k Lag parameter k (j < k).
//' @param bitsize Bit size for modulo (m = 2^bitsize).
//' @param operation Character representing the operation: '+', '-', '*', '^' (XOR).
//' @return NumericVector of generated values.
//' @examples
//' plot(
//' lfg(10000,j=7083 ,k=19937, bitsize=32, operation = '^')
//'   )
//' @export
// [[Rcpp::export]]

 NumericVector lfg(int n, int j = 24, int k = 55, int bitsize = 32, char operation = '+') {

   if (j <= 0 || k <= 0 || k <= j) {
     stop("Invalid lag values: ensure that 0 < j < k.");
   }

   uint64_t m = (1ULL << bitsize);  // modulus: 2^bitsize

   // Initialize seed values with basic Fibonacci-like sequence
   NumericVector state(k);
   state[0] = 1;
   state[1] = 1;
   for (int i = 2; i < k; ++i) {
     state[i] = fmod(state[i - 1] + state[i - 2], m);
   }

   NumericVector result(n);

   // Copy initial k values to result
   for (int i = 0; i < k && i < n; ++i) {
     result[i] = state[i];
   }

   // Generate new values
   for (int i = k; i < n; ++i) {
     double x = result[i - j];
     double y = result[i - k];
     double val = 0;

     switch (operation) {
     case '+':
       val = fmod(x + y, m);
       break;
     case '-':
       val = fmod(x - y + m, m);  // ensure non-negative
       break;
     case '*': {
         uint64_t x_int = static_cast<uint64_t>(x);
         uint64_t y_int = static_cast<uint64_t>(y);
         uint64_t result_int = (x_int * y_int) % m;
         val = static_cast<double>(result_int);
         break;
       }
     case '^':  // XOR using integers
       val = static_cast<double>((static_cast<uint64_t>(x) ^ static_cast<uint64_t>(y)) % m);
       break;
     default:
       stop("Unsupported operation. Use '+', '-', '*', or '^' for XOR.");
     }

     result[i] = val;
   }

   return result;
 }


// Testing
/*** R
plot(
  lfg(10000,j=7083 ,k=19937, bitsize=32, operation = '^')
)

plot(
  lfg(10000,j=7083 ,k=19937, bitsize=32, operation = '-')
)

*/




