#' Comprehensive Randomness Battery
#'
#' Runs a suite of nonparametric randomness tests from the \code{randtests}
#' package.
#'
#' The overall null hypothesis is that the input sequence is randomly ordered,
#' independent, and has no systematic trend or non-random structure. Each test
#' evaluates this null hypothesis from a different perspective, such as runs,
#' ranks, signs of differences, turning points, or monotonic trend.
#'
#' @param x A numeric vector containing the sequence to test for randomness.
#' @param alter Alternative hypothesis. One of \code{"two.sided"},
#'   \code{"less"}, \code{"greater"}, \code{"left.sided"}, or
#'   \code{"right.sided"}. The values \code{"less"} and \code{"greater"} are
#'   mapped internally to \code{"left.sided"} and \code{"right.sided"},
#'   respectively.
#' @param na_rm Logical. If \code{TRUE}, missing values are removed before
#'   testing. If \code{FALSE}, the function throws an error when \code{x}
#'   contains missing values.
#' @param alpha Significance level used to determine the \code{Reject_H0}
#'   column. Default is \code{0.05}.
#'
#' @details
#' The null hypothesis for the full battery is:
#'
#' \deqn{H_0: the sequence is randomly ordered, independent, and contains no systematic pattern.}
#'
#' The tests included are:
#' \describe{
#'   \item{Bartels Rank Test}{Tests whether the observations are randomly ordered,
#'   with no serial dependence or trend.}
#'   \item{Cox Stuart Test}{Tests whether there is no monotonic trend in the
#'   sequence.}
#'   \item{Difference Sign Test}{Tests whether successive differences show no
#'   systematic upward or downward tendency.}
#'   \item{Runs Test}{Tests whether the sequence is randomly ordered around a
#'   reference point, typically the median.}
#'   \item{Turning Point Test}{Tests whether the number of local peaks and
#'   valleys is consistent with randomness.}
#'   \item{Rank Test}{Tests whether the ordering of the observations is random,
#'   with no trend.}
#' }
#'
#' The \code{Reject_H0} column indicates whether each test rejects its null
#' hypothesis at the chosen \code{alpha} level using the raw p-value returned by
#' that test.
#'
#' @return A \code{data.frame} with one row per randomness test and the following
#'   columns:
#' \describe{
#'   \item{Test}{Short name of the randomness test.}
#'   \item{Method}{Method name returned by the underlying \code{randtests}
#'   function.}
#'   \item{Alternative}{Alternative hypothesis used in the test.}
#'   \item{N}{Number of non-missing observations tested.}
#'   \item{Statistic}{Observed test statistic.}
#'   \item{Statistic_Name}{Name of the test statistic, when available.}
#'   \item{Expected_Mu}{Expected value of the statistic under the null
#'   hypothesis, when available.}
#'   \item{Variance}{Variance of the statistic under the null hypothesis, when
#'   available.}
#'   \item{P_Value}{Raw p-value returned by the test.}
#'   \item{Error}{Error message if the test failed; otherwise \code{NA}.}
#'   \item{Reject_H0}{Logical value indicating whether the null hypothesis is
#'   rejected at level \code{alpha} using the raw p-value.}
#' }
#'
#' @examples
#' library(randngen)
#' n <- 10000
#' seed <- 12345
#' lcg_digits <- lcg(n=n, seed=seed)
#' run_randtests(lcg_digits)
#' @export
run_randtests <- function(
    x,
    alter = "two.sided",
    na_rm = TRUE,
    alpha = 0.05
) {
  if (!requireNamespace("randtests", quietly = TRUE)) {
    stop("Please install the 'randtests' package.", call. = FALSE)
  }
  
  if (!is.numeric(x)) {
    stop("`x` must be a numeric vector.", call. = FALSE)
  }
  
  if (!is.logical(na_rm) || length(na_rm) != 1L) {
    stop("`na_rm` must be TRUE or FALSE.", call. = FALSE)
  }
  
  if (na_rm) {
    x <- x[!is.na(x)]
  } else if (anyNA(x)) {
    stop("`x` contains missing values. Use `na_rm = TRUE` to remove them.", call. = FALSE)
  }
  
  if (length(x) < 3L) {
    stop("`x` must contain at least 3 non-missing observations.", call. = FALSE)
  }
  
  if (!is.numeric(alpha) || length(alpha) != 1L || alpha <= 0 || alpha >= 1) {
    stop("`alpha` must be a single number between 0 and 1.", call. = FALSE)
  }
  
  alter <- match.arg(
    alter,
    choices = c("two.sided", "less", "greater", "left.sided", "right.sided")
  )
  
  randtests_alter <- switch(
    alter,
    "less" = "left.sided",
    "greater" = "right.sided",
    alter
  )
  
  test_funcs <- list(
    "Bartels Rank"    = randtests::bartels.rank.test,
    "Cox Stuart"      = randtests::cox.stuart.test,
    "Difference Sign" = randtests::difference.sign.test,
    "Runs Test"       = randtests::runs.test,
    "Turning Point"   = randtests::turning.point.test,
    "Rank Test"       = randtests::rank.test
  )
  
  extract_one <- function(obj, field) {
    value <- obj[[field]]
    
    if (is.null(value) || length(value) == 0L) {
      return(NA_real_)
    }
    
    as.numeric(value[1L])
  }
  
  results <- lapply(names(test_funcs), function(test_name) {
    tryCatch(
      {
        htest_obj <- test_funcs[[test_name]](
          x,
          alternative = randtests_alter
        )
        
        statistic <- htest_obj$statistic
        
        method <- if (is.null(htest_obj$method)) {
          test_name
        } else {
          htest_obj$method
        }
        
        data.frame(
          Test           = test_name,
          Method         = method,
          Alternative    = randtests_alter,
          N              = length(x),
          Statistic      = as.numeric(statistic[1L]),
          Statistic_Name = ifelse(
            is.null(names(statistic)) || names(statistic)[1L] == "",
            NA_character_,
            names(statistic)[1L]
          ),
          Expected_Mu    = extract_one(htest_obj, "mu"),
          Variance       = extract_one(htest_obj, "var"),
          P_Value        = as.numeric(htest_obj$p.value),
          Error          = NA_character_,
          stringsAsFactors = FALSE
        )
      },
      error = function(e) {
        data.frame(
          Test           = test_name,
          Method         = test_name,
          Alternative    = randtests_alter,
          N              = length(x),
          Statistic      = NA_real_,
          Statistic_Name = NA_character_,
          Expected_Mu    = NA_real_,
          Variance       = NA_real_,
          P_Value        = NA_real_,
          Error          = conditionMessage(e),
          stringsAsFactors = FALSE
        )
      }
    )
  })
  
  results <- do.call(rbind, results)
  
  results$Reject_H0 <- ifelse(
    is.na(results$P_Value),
    NA,
    results$P_Value < alpha
  )
  
  rownames(results) <- NULL
  
  results
}