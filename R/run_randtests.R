#' Comprehensive Randomness Battery
#' @param x A numeric vector
#' @param alter Alternative hypothesis: "two.sided" (default), "less", or "greater"
#' @return A data.frame containing detailed diagnostic results
#' @export
run_randtests <- function(x, alter = "two.sided") {
  if (!requireNamespace("randtests", quietly = TRUE)) {
    stop("Please install the 'randtests' package.")
  }
  
  # Define the test suite
  test_funcs <- list(
    "Bartels Rank"    = randtests::bartels.rank.test,
    "Cox Stuart"      = randtests::cox.stuart.test,
    "Difference Sign" = randtests::difference.sign.test,
    "Runs Test"       = randtests::runs.test,
    "Turning Point"   = randtests::turning.point.test,
    "Rank Test"       = randtests::rank.test
  )
  
  # Initialize storage
  n_tests <- length(test_funcs)
  results <- data.frame(
    Method      = character(n_tests),
    Statistic   = numeric(n_tests),
    Expected_Mu = numeric(n_tests),
    Variance    = numeric(n_tests),
    P_Value     = numeric(n_tests),
    stringsAsFactors = FALSE
  )
  
  for (i in seq_along(test_funcs)) {
    # Execute test with provided alternative
    test_name <- names(test_funcs)[i]
    htest_obj <- test_funcs[[i]](x, alternative = alter)
    
    # Fill dataframe using htest components
    results$Method[i]      <- htest_obj$method
    results$Statistic[i]   <- as.numeric(htest_obj$statistic)
    results$Expected_Mu[i] <- ifelse(is.null(htest_obj$mu), NA, htest_obj$mu)
    results$Variance[i]    <- ifelse(is.null(htest_obj$var), NA, htest_obj$var)
    results$P_Value[i]     <- htest_obj$p.value
  }
  
  return(results)
}