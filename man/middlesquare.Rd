% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{middlesquare}
\alias{middlesquare}
\title{Middles-Square Method}
\usage{
middlesquare(seed, n)
}
\arguments{
\item{seed}{initial starting value}

\item{n}{number of random numbers desired}
}
\description{
The middle-square method is a method for generating pseudorandom numbers. In practice it is highly flawed for many practical purposes. Its period is usually very short and it possesses some severe weaknesses. Repeated enough times, the middle-square method will either begin repeatedly generating the same number or cycle to the previous number in a sequence and loop indefinitely.
}
\details{
Despite its weaknesses, the middle-square method is a good introductory example for how pseudorandom number generators work. This C++ code is based on the python code shared on Wikipedia (\href{https://en.wikipedia.org/wiki/Middle-square_method#Example_implementation}{link}). For more information check out the \href{https://en.wikipedia.org/wiki/Middle-square_method}{Wikipedia}
}
\examples{
random_numbers <- middlesquare(1234, 1000)
# Plot numbers to see that they are random
plot(random_numbers)
}
