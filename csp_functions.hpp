#ifndef CSP_FUNCTIONS_HPP
#define CSP_FUNCTIONS_HPP

#include "z3++.h"

z3::expr alive_neighbors(z3::context &c, z3::expr_vector game_matrix, int i, int j, int n, int m);

#endif