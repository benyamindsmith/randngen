#include <Rcpp.h>
using namespace Rcpp;
// This code is based on the python code shared on Wikipedia: https://en.wikipedia.org/wiki/Middle-square_method
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
