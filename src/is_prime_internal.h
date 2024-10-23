#ifndef IS_PRIME_H
#define IS_PRIME_H

#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;


// Helper function to check if a number is prime
bool is_prime_internal(int num) {
  if (num <= 1) return false;
  if (num == 2 || num == 3) return true;
  if (num % 2 == 0 || num % 3 == 0) return false;

  for (int i = 5; i * i <= num; i += 6) {
    if (num % i == 0 || num % (i + 2) == 0) return false;
  }

  return true;
}



#endif
