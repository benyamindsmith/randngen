#' Scale Numeric Vector to Range [0, 1]
#'
#' This function scales a numeric vector to a range between 0 and 1. Primarily intended for
#' processing output from Pseudorandom Number Generators (PRNGs), this scaling
#' transforms values into a standardized range, facilitating downstream analysis
#' and comparative studies.
#'
#' The formula used for rescaling each element \eqn{x_i} in the vector \eqn{x} is:
#' \deqn{x_{scaled} = \frac{x_i - \text{min}(x)}{\text{max}(x) - \text{min}(x)}}
#'
#' This method of normalization ensures values are linearly scaled, and is commonly used
#' in probabilistic modeling, machine learning, and simulations to transform data
#' into a uniform range [0, 1]. Note that the method may produce NaN values if
#' `x` is a constant vector, which is handled as a special case.
#'
#' @param x A numeric vector containing values from a PRNG or other numeric data.
#'
#' @return A numeric vector where each element is rescaled to fall within the range [0, 1].
#' If all values in `x` are identical, the function returns a vector of zeros of the same length.
#'
#' @references
#' - StackOverflow. (2011). Scale a series between two points.
#'   Retrieved from \url{https://stackoverflow.com/questions/5468280/scale-a-series-between-two-points}
#' - Wikipedia contributors. (2023). Feature scaling. In *Wikipedia, The Free Encyclopedia*.
#'   Retrieved from \url{https://en.wikipedia.org/wiki/Feature_scaling}
#'
#' @examples
#' # Example with PRNG values
#' set.seed(42)
#' prng_values <- runif(10, min = -5, max = 5)
#' scaled_values <- scale_to_01(prng_values)
#' print(scaled_values)
#'
#' @export
scale_to_01 <- function(x) {
  # Check if the input is numeric
  if (!is.numeric(x)) {
    stop("Input vector 'x' must be numeric.")
  }

  # Calculate min and max of the vector
  x_min <- min(x, na.rm = TRUE)
  x_max <- max(x, na.rm = TRUE)

  # Handle the case where all elements are the same
  if (x_min == x_max) {
    warning("All elements in 'x' are identical; returning a vector of zeros.")
    return(rep(0, length(x)))
  }

  # Scale values to the range [0, 1]
  (x - x_min) / (x_max - x_min)
}
