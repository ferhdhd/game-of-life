#ifndef CSP_FUNCTIONS_HPP
#define CSP_FUNCTIONS_HPP

#include <vector>
#include "z3++.h"

z3::expr alive_neighbors(z3::context &c, z3::expr_vector game_matrix, int i, int j, int n, int m);

std::vector<int> read_matrix(int n, int m);

void print_matrix(const std::vector<int>& mat, int n, int m);

z3::expr_vector create_variables(z3::context& c, int n, int m);

void add_domain_constraints(z3::optimize& solver, const z3::expr_vector& vars, int n, int m);

void add_restrictions(z3::optimize& solver, z3::context& c, const z3::expr_vector& vars, const std::vector<int>& mat_og, int n, int m);

void add_objective(z3::optimize& solver, z3::context& c, const z3::expr_vector& vars, int n, int m);

void print_solution(const z3::model& mod, const z3::expr_vector& vars, int n, int m);

#endif