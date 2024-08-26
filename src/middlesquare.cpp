#include <Rcpp.h>
using namespace Rcpp;
//' Middles-Square Method
//'
//' The middle-square method is a method for generating pseudorandom numbers. In practice it is highly flawed for many practical purposes. Its period is usually very short and it possesses some severe weaknesses. Repeated enough times, the middle-square method will either begin repeatedly generating the same number or cycle to the previous number in a sequence and loop indefinitely.
//'
//' Despite its weaknesses, the middle-square method is a good introductory example for how pseudorandom number generators work. This C++ code is based on the python code shared on Wikipedia (\href{https://en.wikipedia.org/wiki/Middle-square_method#Example_implementation}{link}). For more information check out the \href{https://en.wikipedia.org/wiki/Middle-square_method}{Wikipedia}
//'
//'
//' @param seed initial starting value
//' @param n number of random numbers desired
//' @examples
//' random_numbers <- middlesquare(1234, 1000)
//' # Plot numbers to see that they are random
//' plot(random_numbers)
//' @export
// [[Rcpp::export]]

NumericVector middlesquare(int seed, int n) {
  NumericVector generated_numbers;
  int number = seed;
  for (int i = 0; i < n; ++i) {
    // Calculate square of number
    long long squared = (long long)number * number;
    // Convert squared number to string
    std::string squared_str = std::to_string(squared);
    // Pad with zeros if length is less than 8
    if (squared_str.length() < 8) {
      squared_str = std::string(8 - squared_str.length(), '0') + squared_str;
    }
    // Extract middle digits
    std::string middle_digits = squared_str.substr(2, 4);
    // Update number
    number = std::stoi(middle_digits);
    // Store generated number
    generated_numbers.push_back(number);

  }
  return generated_numbers;
}
