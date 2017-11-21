//  Copyright © 2016 Meng Li. All rights reserved.
//  Copyright © 2017 Daniel Bourgeois. All rights reserved.

#include "RcppArmadillo.h"
#include "tree_class.hpp"

// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::vec tree_likelihood(
  arma::vec const& obs,
  arma::vec const& dimension_vec,
  arma::mat const& hyper_grid)
{
  using namespace arma;

  class_tree tree_test(obs, dimension_vec);

  int n_grid = hyper_grid.n_cols;
  vec ml_mat(n_grid);

  for (int i = 0; i < n_grid; i++)
  {
    vec hyper = hyper_grid.col(i);
    mat par = tree_test.hyper2par(hyper);
    double ml = tree_test.marginal_likelihood(par);
    ml_mat(i) = ml;
  }

  return ml_mat;
}
