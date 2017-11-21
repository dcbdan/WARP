#  Copyright © 2016 Meng Li. All rights reserved.
#  Copyright © 2017 Daniel Bourgeois. All rights reserved.

hyper_default <- function(
  obs,
  dimension,
  pruning = TRUE)
{
  num_obs <- length(obs)
  total_level <- log(num_obs, base = 2)
  idx <- seq(2, num_obs, by = 2)
  a <- (obs[idx] - obs[idx-1]) / sqrt(2)
  sigma_hat <- median(abs(a-median(a))) * 1.4826

  eta_list <- c(0.3, 0.4, 0.5)

  n_value <- c(3, 3, 1, length(eta_list))
  n_grid <- prod(n_value)

  last_tau <- 1/(sigma_hat^2) * rep(1:3/10, n_grid/n_value[1])
  last_rho <- rep(1:3/10, n_grid/n_value[2])
  beta = 1
  alpha = rep(0.5, n_grid/n_value[3])
  eta = rep(eta_list, n_grid/n_value[4])
  adjust = numeric(n_grid)
  hyper = rbind(
    log(beta) + adjust,
    log(last_rho) + log(2) * beta * total_level,
    -log(1/eta - 1) + adjust,
    log(alpha) + adjust,
    log(last_tau) + alpha * total_level * log(2),
    log(sigma_hat) + adjust)

  corr_likelihoods <- tree_likelihood(obs, dimension, hyper)
  return(hyper[,which.max(corr_likelihoods)])
}
