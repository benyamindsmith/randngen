#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

//' Fibonacci Linear Feedback Shift Register (LFSR)
//'
//' This function generates a sequence of numbers using a Fibonacci Linear Feedback Shift Register (LFSR).
//' LFSR is a shift register that produces a pseudo-random sequence of binary numbers based on the initial seed value and the feedback configuration.
//'
//' @param seed A large integer (64-bit) representing the initial value of the LFSR.
//' @param n Integer specifying the number of numbers to generate.
//' @param bitsize Integer specifying the number of bits in the LFSR. This determines the register's length.
//' @param taps A numeric vector specifying the tap positions used to calculate the feedback bit. The values should correspond to bit positions (1-based indexing).
//'
//' @return A numeric vector containing the sequence of generated numbers from the LFSR.
//'
//' @details
//' The function implements a Fibonacci LFSR, where the feedback bit is computed by XOR-ing selected bits (as determined by the tap positions). The register is then shifted, and the feedback bit is inserted into the most significant position.
//'
//' @examples
//' # Generate a sequence of 10 numbers using an LFSR with a 16-bit register, a seed of 12345, and tap positions at 16 and 14
//' lfsr_fib(12345, 10, 16, c(16, 14))
//'
//' @seealso \href{https://en.wikipedia.org/wiki/Linear-feedback_shift_register}{Linear Feedback Shift Register on Wikipedia}
//'
//' @export
// [[Rcpp::export]]

 NumericVector lfsr_fib(long long seed, int n, int bitsize, NumericVector taps) {
   NumericVector generated_numbers;
   long long lfsr = seed;
   long long bit;

   for(int i = 0; i < n; i++) {
     // Compute the feedback bit using XOR over the tap positions
     bit = 0;  // Reset bit to 0
     for(int j = 0; j < taps.size(); j++) {
       bit ^= (lfsr >> (static_cast<int>(taps[j]) - 1)) & 1;  // Cast tap to int and use for XOR
     }

     // Shift the LFSR and insert the new bit at the most significant position
     lfsr = (lfsr >> 1) | (bit << (bitsize - 1));

     // Store the current LFSR value in the generated numbers
     generated_numbers.push_back(lfsr);
   }

   return generated_numbers;
 }



//' Galois Linear Feedback Shift Register
//'
//' For more information, check out the \href{https://en.wikipedia.org/wiki/Linear-feedback_shift_register}{Wikipedia Page}.
// [[Rcpp::export]]

NumericVector lfsr_galois(long long seed, int n, int bitsize, NumericVector taps){
  NumericVector generated_numbers;
  long long start_state = seed;

  for(int i=0; i < n; i++){

  }
  return generated_numbers;
}

//' Xorshift Linear Feedback Shift Register
//'
//' For more information, check out the \href{https://en.wikipedia.org/wiki/Linear-feedback_shift_register}{Wikipedia Page}.
// [[Rcpp::export]]

NumericVector lfsr_xorshift(long long seed, int n, int bitsize, NumericVector taps){
  NumericVector generated_numbers;
  long long start_state = seed;

  for(int i=0; i < n; i++){


  }
  return generated_numbers;
}

// Testing
/*** R
lfsr_fib(seed = 12345, n = 1000, bitsize = 16, taps =c(1, 3,4,6))|>
  plot()
*/
