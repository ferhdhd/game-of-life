#include <iostream>
#include "csp_functions.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    z3::context c;
    z3::optimize solver(c);

    std::vector<int> mat_og = read_matrix(n, m);

    z3::expr_vector game_matrix = create_variables(c, n, m);
    add_domain_constraints(solver, game_matrix, n, m);
    add_restrictions(solver, c, game_matrix, mat_og, n, m);
    add_objective(solver, c, game_matrix, n, m);

    if (solver.check() == z3::sat) {
        z3::model mod = solver.get_model();
        print_solution(mod, game_matrix, n, m);
    } else {
        std::cout << n << m << std::endl;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << "0 ";
            }
            std::cout << std::endl;
        }
    }   
    return 0;
}
