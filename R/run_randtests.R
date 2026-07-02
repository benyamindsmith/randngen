#' Comprehensive Randomness Battery
#'
#' Runs a suite of nonparametric randomness tests from the `randtests` package.
#'
#' @param x A numeric vector.
#' @param alter Alternative hypothesis. Accepts:
#'   "two.sided" default, "less", "greater", "left.sided", or "right.sided".
#'   "less" is mapped to "left.sided"; "greater" is mapped to "right.sided".
#' @param na_rm Logical. If TRUE, missing values are removed before testing.
#' @param alpha Significance level used for the Reject_H0 column. Default is 0.05.
#' @param p_adjust_method Method for multiple-testing adjustment. Default is "none".
#' @importFrom stats p.adjust
#' @return A data.frame containing diagnostic results for each randomness test.
#' @export
run_randtests <- function(
    x,
    alter = "two.sided",
    na_rm = TRUE,
    alpha = 0.05,
    p_adjust_method = "none"
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
  
  results$P_Adjusted <- p.adjust(
    results$P_Value,
    method = p_adjust_method
  )
  
  results$Reject_H0 <- ifelse(
    is.na(results$P_Adjusted),
    NA,
    results$P_Adjusted < alpha
  )
  
  rownames(results) <- NULL
  
  results
}