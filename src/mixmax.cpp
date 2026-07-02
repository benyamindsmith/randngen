#include <Rcpp.h>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

//' MIXMAX Random Number Generator
//'
//' Generate pseudorandom numbers using a simple Rcpp implementation of the
//' MIXMAX random number generator.
//'
//' MIXMAX is a family of pseudorandom number generators based on matrix
//' recurrences over the finite field with Mersenne modulus \eqn{2^{61} - 1}.
//' This function keeps the interface similar to other simple RNG functions:
//' provide a seed, the number of values to generate, and optional controls.
//'
//' @param seed Integer seed. For `"lcg"` and `"spbox"` seeding, `seed` must
//'   satisfy `0 < seed < 2^61 - 1`. When `seed_method = "vielbein"`, the seed
//'   is ignored.
//' @param n Number of pseudorandom values to generate. Must be non-negative.
//' @param N MIXMAX matrix size. Supported values are `3150`, `1260`, `1000`,
//'   `720`, `508`, `256`, `88`, `64`, `44`, `40`, `30`, `16`, and `10`.
//'   The default is `256`.
//' @param seed_method Seeding method. One of `"lcg"`, `"spbox"`, or
//'   `"vielbein"`. The default is `"lcg"`.
//' @param vielbein_index Basis-vector index used only when
//'   `seed_method = "vielbein"`. Must satisfy `1 <= vielbein_index <= N`.
//' @param burn_in Number of generated values to discard before returning
//'   output. Must be non-negative.
//' @param burn_in_cycles Number of full MIXMAX state-vector updates to discard
//'   before returning output. Must be non-negative.
//' @param start_after_seed Logical. If `TRUE`, advance the full MIXMAX state
//'   once immediately after seeding.
//' @param scaling Scaling method for returned uniform values. One of
//'   `"mersenne"`, `"half_open"`, or `"open"`.
//'   `"mersenne"` returns `raw / (2^61 - 1)`.
//'   `"half_open"` returns `raw / 2^61`.
//'   `"open"` returns `(raw + 0.5) / 2^61`.
//' @param raw Logical. If `FALSE`, return scaled uniform values. If `TRUE`,
//'   return raw 61-bit integer values stored as doubles. Note that R doubles
//'   cannot exactly represent every 61-bit integer.
//' @param warn_small_N Logical. If `TRUE`, warn when `N < 88`.
//'
//' @return A numeric vector of length `n`.
//'
//' @details
//' The default call `mixmax(seed = 12345, n = 10000)` uses `N = 256`,
//' LCG-style seeding, no burn-in, and Mersenne scaling.
//'
//' This function is self-contained and does not use or modify R's global random
//' number generator state.
//'
//' @examples
//' x <- mixmax(seed = 12345, n = 10000)
//' plot(x, type = "l")
//'
//' hist(
//'   mixmax(seed = 12345, n = 10000),
//'   breaks = 50,
//'   main = "MIXMAX RNG",
//'   xlab = "Generated values"
//' )
//'
//' # Larger matrix size
//' x_big <- mixmax(seed = 12345, n = 10000, N = 3150)
//'
//' # SPBOX seeding
//' x_spbox <- mixmax(seed = 12345, n = 10000, seed_method = "spbox")
//'
//' # Burn-in
//' x_burn <- mixmax(seed = 12345, n = 10000, burn_in = 1000)
//'
//' # Burn-in by full state cycles
//' x_cycles <- mixmax(seed = 12345, n = 10000, burn_in_cycles = 10)
//'
//' # Different scaling choices
//' x1 <- mixmax(12345, 10000, scaling = "mersenne")
//' x2 <- mixmax(12345, 10000, scaling = "half_open")
//' x3 <- mixmax(12345, 10000, scaling = "open")
//'
//' # Raw values as doubles
//' raw_values <- mixmax(12345, 10, raw = TRUE)
//'
//' @export
// [[Rcpp::export]]
NumericVector mixmax(
   long long seed,
   int n,
   int N = 256,
   std::string seed_method = "lcg",
   int vielbein_index = 1,
   int burn_in = 0,
   int burn_in_cycles = 0,
   bool start_after_seed = false,
   std::string scaling = "mersenne",
   bool raw = false,
   bool warn_small_N = true
) {
 
 using u64 = std::uint64_t;

 const u64 MERSBASE = (1ULL << 61) - 1ULL;
 const u64 MULT = 1073217536ULL;
 
 if (n < 0)
   stop("n must be >= 0");
 
 if (N < 2)
   stop("N must be at least 2");
 
 if (burn_in < 0)
   stop("burn_in must be >= 0");
 
 if (burn_in_cycles < 0)
   stop("burn_in_cycles must be >= 0");
 
 std::transform(
   seed_method.begin(), seed_method.end(), seed_method.begin(),
   [](unsigned char c) { return std::tolower(c); }
 );
 
 std::transform(
   scaling.begin(), scaling.end(), scaling.begin(),
   [](unsigned char c) { return std::tolower(c); }
   );
   
 long long special;
 
 switch (N) {
 case 3150: special = -11LL; break;
 case 1260: special =  15LL; break;
 case 1000: special =   0LL; break;
 case  720: special =   1LL; break;
 case  508: special =   5LL; break;
 case  256: special =  -1LL; break;
 case   88: special =   1LL; break;
 case   64: special =   6LL; break;
 case   44: special =   0LL; break;
 case   40: special =   1LL; break;
 case   30: special =   3LL; break;
 case   16: special =   6LL; break;
 case   10: special =  -1LL; break;
 default:
   stop("Possible values for N are: 3150, 1260, 1000, 720, 508, 256, 88, 64, 44, 40, 30, 16, 10");
 }
 
 if (warn_small_N && N < 88)
   warning("MIXMAX matrix sizes below 88 are known not to pass all statistical tests");
 
 if (seed_method != "lcg" &&
       seed_method != "spbox" &&
       seed_method != "vielbein")
     stop("seed_method must be one of: 'lcg', 'spbox', or 'vielbein'");
 
 if (scaling != "mersenne" &&
     scaling != "half_open" &&
     scaling != "open")
   stop("scaling must be one of: 'mersenne', 'half_open', or 'open'");
 
 if (seed_method != "vielbein") {
   if (seed <= 0)
       stop("seed must be > 0");
     
     if (static_cast<u64>(seed) >= MERSBASE)
       stop("seed must be less than 2^61 - 1");
   }
   
   if (seed_method == "vielbein") {
     if (vielbein_index < 1 || vielbein_index > N)
       stop("vielbein_index must satisfy 1 <= vielbein_index <= N");
   }
   
   auto mod_mersenne = [&](u64 x) -> u64 {
     return (x & MERSBASE) + (x >> 61);
   };
   
   auto modmulM61 = [&](u64 a, u64 b) -> u64 {
     u64 result = 0ULL;
     
     while (b > 0ULL) {
       if ((b & 1ULL) == 1ULL)
         result = mod_mersenne(result + a);
       
       a = mod_mersenne(a << 1);
       b >>= 1;
     }
     
     return result;
   };
   
   auto mod_mulspec = [&](u64 x) -> u64 {
     if (special == 0LL)
       return 0ULL;
     
     if (special == 1LL)
       return x;
     
     if (special == -1LL)
       return MERSBASE - x;
     
     if (special > 0LL)
       return modmulM61(x, static_cast<u64>(special));
     
     return MERSBASE - modmulM61(x, static_cast<u64>(-special));
   };
   
   auto to_uniform = [&](u64 x) -> double {
     if (scaling == "mersenne")
       return static_cast<double>(x) / static_cast<double>(MERSBASE);
     
     if (scaling == "half_open")
       return static_cast<double>(x) / std::ldexp(1.0, 61);
     
     return (static_cast<double>(x) + 0.5) / std::ldexp(1.0, 61);
   };
   
   std::vector<u64> V(N);
   u64 sumtot = 0ULL;
   
   if (seed_method == "lcg") {
     
     V[0] = static_cast<u64>(seed) & MERSBASE;
     
     for (int i = 1; i < N; ++i) {
       V[i] = modmulM61(V[i - 1], MULT);
       sumtot = mod_mersenne(sumtot + V[i]);
     }
     
   } else if (seed_method == "spbox") {
     
     const u64 MULT64 = 6364136223846793005ULL;
     u64 l = static_cast<u64>(seed);
     
     V[0] = static_cast<u64>(seed) & MERSBASE;
     
     for (int i = 1; i < N; ++i) {
       l = l * MULT64;
       l = (l << 32) ^ (l >> 32);
       
       V[i] = l & MERSBASE;
       sumtot = mod_mersenne(sumtot + V[i]);
     }
     
   } else {
     
     for (int i = 0; i < N; ++i)
       V[i] = 0ULL;
     
     V[vielbein_index - 1] = 1ULL;
     sumtot = 0ULL;
   }
   
   auto fill_rnd = [&]() {
     u64 tmp2 = V[1];
     
     V[0] = mod_mersenne(V[0] + sumtot);
     
     u64 tmpP = V[1];
     V[1] = mod_mersenne(V[0] + V[1]);
     sumtot = V[1];
     
     for (int i = 2; i < N; ++i) {
       tmpP = mod_mersenne(V[i] + tmpP);
       V[i] = mod_mersenne(V[i - 1] + tmpP);
       sumtot = mod_mersenne(sumtot + V[i]);
     }
     
     if (special != 0LL) {
       tmp2 = mod_mulspec(tmp2);
       V[2] = mod_mersenne(V[2] + tmp2);
       sumtot = mod_mersenne(sumtot + tmp2);
     }
   };
   
   int cnt = 0;
   
   if (seed_method == "vielbein")
     cnt = N;
   
   if (start_after_seed) {
     fill_rnd();
     cnt = 0;
   }
   
   for (int i = 0; i < burn_in_cycles; ++i) {
     fill_rnd();
     cnt = 0;
   }
   
   auto next_raw = [&]() -> u64 {
     if (cnt >= N) {
       fill_rnd();
       cnt = 0;
     }
     
     u64 out = V[cnt];
     ++cnt;
     
     return out;
   };
   
   for (int i = 0; i < burn_in; ++i)
     next_raw();
   
   NumericVector generated_numbers(n);
   
   for (int i = 0; i < n; ++i) {
     u64 value = next_raw();
     
     if (raw)
       generated_numbers[i] = static_cast<double>(value);
     else
       generated_numbers[i] = to_uniform(value);
   }
   
   return generated_numbers;
 }

/*** R
# Basic usage, 
x <- mixmax(seed = 12345, n = 10000)
plot(x, type = "l")

# Histogram
hist(
  mixmax(seed = 12345, n = 10000),
  breaks = 50,
  main = "MIXMAX RNG",
  xlab = "Generated values"
)

# Use a larger MIXMAX matrix size
x_big <- mixmax(seed = 12345, n = 10000, N = 3150)

# Use SPBOX seeding instead of LCG seeding
x_spbox <- mixmax(
  seed = 12345,
  n = 10000,
  seed_method = "spbox"
)

# Discard first 1000 generated values
x_burn <- mixmax(
  seed = 12345,
  n = 10000,
  burn_in = 1000
)

# Advance by 10 full MIXMAX state cycles before generating
x_cycles <- mixmax(
  seed = 12345,
  n = 10000,
  burn_in_cycles = 10
)

# Force the generator to advance once after seeding
x_advanced <- mixmax(
  seed = 12345,
  n = 10000,
  start_after_seed = TRUE
)

# Different scaling choices
x1 <- mixmax(12345, 10000, scaling = "mersenne")   # raw / (2^61 - 1)
x2 <- mixmax(12345, 10000, scaling = "half_open")  # raw / 2^61
x3 <- mixmax(12345, 10000, scaling = "open")       # (raw + 0.5) / 2^61

*/