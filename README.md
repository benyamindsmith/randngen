# randgen <a href='https://github.com/benyamindsmith/randngen'><img src='https://raw.githubusercontent.com/benyamindsmith/randngen/main/logo.png' align="right" height="300" /></a>    
  <a target="_blank" href="https://discord.gg/VX3pzJyfSw"><img src="https://dcbadge.limes.pink/api/server/VX3pzJyfSw" alt="" /></a>  

<!--
Adding a webhook
This is some text
--->
A opinionated R library of pseudo-random number generators written in C++.

This package aims to be comprehensive with having all popular and emerging random number generators. This package can be used for research and for exploring the properties of random number generators as well. 

![](https://github.com/user-attachments/assets/24323dfd-ed8b-4120-ab3d-605864d42cc1)

## Installing this Package

```r
devtools::install_github("benyamindsmith/randngen")
```
## Random Number Generators Available in this Package

The following is a list of supported random number generators in this package. 

(Based off of the [this Wikipedia Page](https://en.wikipedia.org/wiki/List_of_random_number_generators))

- [x] Middle Square (`middlesquare(seed, n)`)

- [x] Park-Miller (`lcg_parkmiller(seed, n)`)

- [x] Linear Congruential Generator (`lcg(seed, n, m, a, c)`)

- [x] Lagged Fibonacci Generator (`lfg(n, j=65, k=71, bitsize=32, operation = '+')`)

- [x] Linear Feedback Shift Register (`lfsr_fibbonacci(seed, n, bitsize, taps)` & `lfsr_galois(seed, n, bitsize, taps)`)

- [x] Winchmann-Hill (`winchman_hill(seed1, seed2, seed3, n)`)

- [x] Inversive Congruential Generator (`icg(q, a, c, seed,n)`)

- [x] Blumb Blumb Shub (`blumb_blumb_shub(seed, p, q, n)`)

- [x] ACORN (`acorn(seed, n, k, M)`)

- [ ] MIXMAX [NOT STARTED]

- [ ] Add-with-carry (AWC) [NOT STARTED]

- [ ] Subtract-with-borrow (SWB) [NOT STARTED]

- [ ] Maximally periodic reciprocals [NOT STARTED]

- [ ] KISS [NOT STARTED]

- [x] Multiply-with-carry (MWC) (`mwc(seed, n, b = 4294967296, a = 7, c =4)`)

- [ ] Complementary-multiply-with-carry (CMWC)  [NEEDS WORK]

- [ ] Mersenne Twister (MT)  [NOT STARTED]

- [x] Xorshift (`xorshift_32(seed, n)`, `xorshift_64(seed, n)` & `xorshift_128(seed1, seed2, seed3, seed4, n)`) [PLENTY MORE IMPLEMENTATIONS BUT HAPPY FOR NOW]

- [ ] Well equidistributed long-period linear (WELL)  [NOT STARTED]

- [ ] A small noncryptographic PRNG (JSF)  [NOT STARTED]

- [ ] Advanced Randomization System (ARS)  [NOT STARTED]

- [ ] Threefry  [NOT STARTED]

- [ ] Philox  [NOT STARTED]

- [ ] WELLDOC  [NOT STARTED]

- [ ] SplitMix  [NOT STARTED]

- [ ] Permuted Congruential Generator (PCG)  [NOT STARTED]

- [ ] Random Cycle Bit Generator (RCB)  [NOT STARTED]

- [ ] Middle-Square Weyl Sequence RNG (see also middle-square method)  [NOT STARTED]

- [ ] Xoroshiro128+  [NOT STARTED]

- [ ] 64-bit MELG (MELG-64) [NOT STARTED]

- [ ] Squares RNG  [NOT STARTED]

- [ ] L'Ecuyer-CMRG [NOT STARTED]

- [ ] Marsaglia-Multicarry [NOT STARTED]

- [ ] Knuth-TAOCP-2002 [NOT STARTED]

- [ ] Knuth-TAOCP [NOT STARTED]

- [ ] Rule 30 [NOT STARTED]

## Contributing

Since this project is very much in its infancy, there is alot of opportunity to contribute! Some areas include

- Development
- Documentation
- Code Review
- and more!

To get involved, feel free to open up and issue and submit a PR. 

## Future Work

After building out a significant amount of random number generators and doing the appropriate documentation. Next steps would be to either a utility package or a suite of functions within this package that will implement [Diehard tests](https://en.wikipedia.org/wiki/Diehard_tests) and [TestU1 tests](https://en.wikipedia.org/wiki/TestU01).

## Similar Packages and Inspiration

- [The `PRNG` R package](https://cran.r-project.org/web/packages/PRNG/PRNG.pdf)

- [The `miranda` R package](https://github.com/coolbutuseless/miranda)

- [The `dqrng` R package](https://github.com/daqana/dqrng)

- [The `random` C++ library](https://en.cppreference.com/w/cpp/numeric/random)

- [The `sitmo` R package](https://github.com/coatless-rpkg/sitmo)
- 
- [PyRandLib](https://github.com/schmouk/PyRandLib) 

- [PractRand](https://github.com/tylov-fork/PractRand)


