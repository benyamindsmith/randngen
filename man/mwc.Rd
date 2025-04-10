% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{mwc}
\alias{mwc}
\title{Multiply With Carry (MWC)}
\usage{
mwc(seed, n, b = 4294967296, a = 7L, c = 4L)
}
\arguments{
\item{seed}{initial starting value}

\item{n}{number of random numbers desired to be generated}

\item{b}{by default set to \eqn{2^{32} = 4294967296}}

\item{a}{by default set to 7}

\item{c}{by default set to 4}
}
\description{
The multiply-with-carry (MWC) method is a method invented by \href{https://en.wikipedia.org/wiki/George_Marsaglia}{George Marsaglia} for generating sequences of random integers based on an initial set of from two to many thousands of randomly chosen seed values. The main advantages of the MWC method are that it invokes simple computer integer arithmetic and leads to very fast generation of sequences of random numbers with immense periods, ranging from around \eqn{2^{60}} to \eqn{2^{20000000}}.
}
\details{
A MWC generator is a special form of a Lehmer Random Number Generator (see \code{\link{lcg_parkmiller}}) \eqn{x_n=bx_{n-1} \mod p} which allows efficient implementation of a prime modulus \eqn{p} much larger than the machine word size.

Normal Lehmer generator implementations choose a modulsus close to the machine word size. A MWC generator instead maintains its state it base \eqn{b}, so multiplying by \eqn{b} is done implicitly by shifting one word. The base \eqn{b} is typically chosen to equal the computer's word size, as this makes the arithmetic modulo \eqn{b} trivial. This may vary from \eqn{b=2^8} for a microcontroller to \eqn{b=2^{64}}.

The initial seed values are arbitrary,except that they must not all e zero, nor at the maximum permitted values (\eqn{x_0 =b-1 \text{ and } c_0 = a-1}).

The \code{mwc()} function implements creates a lag-1 MWC with the seed values. That is:

\eqn{x_n = (ax_{n-1} + c_{n-1}) \mod b, c = \lfloor{\frac{ax_{n-1}+c_{n-1}}{b}} \rfloor}

For more information, see the \href{https://en.wikipedia.org/wiki/Multiply-with-carry_pseudorandom_number_generator}{Wikipedia page}.
}
\examples{
random_numbers <- mwc(6793,1000)
# Plot numbers to see that they are random
plot(random_numbers)
}
