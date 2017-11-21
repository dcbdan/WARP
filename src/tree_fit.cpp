//  Copyright © 2016 Meng Li. All rights reserved.
//  Copyright © 2017 Daniel Bourgeois. All rights reserved.

#include "RcppArmadillo.h"
#include "tree_class.hpp"

// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::mat tree_fit(
  const arma::colvec & obs,
  const arma::colvec & dimension_vec,
  const arma::colvec & hyper,
  const int & step)
{
  using namespace arma;

  // Perform calculations
  class_tree tree_test(obs, dimension_vec);
  mat par = tree_test.hyper2par(hyper);
  mat BMA = tree_test.fit_tree_cs(par, step);

  return BMA;
}
