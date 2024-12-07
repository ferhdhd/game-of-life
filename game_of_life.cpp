#include <iostream>
#include "csp_functions.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    z3::context c;
    z3::optimize solver(c);

    std::vector<int> mat_og = read_matrix(n, m);
    print_matrix(mat_og, n, m);

    z3::expr_vector game_matrix = create_variables(c, n, m);
    add_domain_constraints(solver, game_matrix, n, m);
    add_restrictions(solver, c, game_matrix, mat_og, n, m);
    add_objective(solver, c, game_matrix, n, m);

    if (solver.check() == z3::sat) {
        std::cout << "Solução encontrada" << std::endl;
        z3::model mod = solver.get_model();
        print_solution(mod, game_matrix, n, m);
    } else {
        std::cout << "Nenhuma solução encontrada." << std::endl;
    }

    return 0;
}
