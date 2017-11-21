//
//  tree_class.hpp
//  Surfing
//
//  Created by Meng Li on 7/15/16.
//  Copyright � 2016 Meng Li. All rights reserved.
//

#ifndef tree_class_hpp
#define tree_class_hpp

#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "RcppArmadillo.h"

using namespace std;
using namespace arma;

// define the tree class
class class_tree
{
public:
    vec obs;
    uvec dimension;

    class_tree(const vec& obs_input, const vec& dimension_input); // constructor: generate dictionary

    vec get_phi_map(const mat& par, const vec& w_d, const vec& ss_adjust); // obtain log_phi

    vec get_M_d_map(const mat& par); // obtain log(M_d)

    vec get_lambda_map(const mat& par); // obtain log(lambda_d)

    double marginal_likelihood(const mat& par); // marginal likelihood

    mat hyper2par(const vec &x); // re-parameterization for optim

    vec fit_tree(const mat& par, const vec& shift_vec); // estimtation without cycle spinning
    vec fit_tree_cs(const mat& par, int step); // estimation via cycle spinning;

//private:
    uword N, total_level, m, pair_N, N_prime;
    uvec node_idx_d, left_idx_d, right_idx_d, compact_idx_map, num_child, level, pair_level, pair_direction;
    field<uvec> flag_first, flag_not_first, F;
    vec n_A, num_child_double, ss_adjust_orig, w_d_orig;
    vec y, ss;

    // used for matlab trials - didn't export these var's in the past
    umat rank_left_child_2, rank_right_child_2, dividible_2; //'_2': questionable - remove finally
    double rescale_sum;
};

#endif /* tree_class_hpp */
