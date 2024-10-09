#ifndef GCD_H
#define GCD_H

#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;


// Helper function to check if two numbers are relatively prime(gcd = 1)
long long gcd_internal(long long a, long long b) {
  while (b != 0) {
    long long temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}


#endif
