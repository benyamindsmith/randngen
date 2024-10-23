#ifndef GCD_H
#define GCD_H

#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;


// Helper function to check if two numbers are relatively prime(gcd = 1)
int gcd_internal(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}


#endif
