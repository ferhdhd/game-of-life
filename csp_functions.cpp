#include "csp_functions.hpp"

z3::expr alive_neighbors(z3::context &c, z3::expr_vector game_matrix, int i, int j, int n, int m) {
    z3::expr num_alive = c.int_val(0);

    if ((j - 1) >= 0) {
        num_alive = num_alive + z3::ite(game_matrix[i * m + (j - 1)] == 1, c.int_val(1), c.int_val(0));
    }
    if ((j - 1) >= 0 && (i - 1) >= 0) {
        num_alive = num_alive + z3::ite(game_matrix[(i - 1) * m + (j - 1)] == 1, c.int_val(1), c.int_val(0));
    }
    if ((j - 1) >= 0 && (i + 1) < n) {
        num_alive = num_alive + z3::ite(game_matrix[(i + 1) * m + (j - 1)] == 1, c.int_val(1), c.int_val(0));
    }
    if ((i - 1) >= 0) {
        num_alive = num_alive + z3::ite(game_matrix[(i - 1) * m + j] == 1, c.int_val(1), c.int_val(0));
    }
    if ((i + 1) < n) {
        num_alive = num_alive + z3::ite(game_matrix[(i + 1) * m + j] == 1, c.int_val(1), c.int_val(0));
    }
    if ((j + 1) < m) {
        num_alive = num_alive + z3::ite(game_matrix[i * m + (j + 1)] == 1, c.int_val(1), c.int_val(0));
    }
    if ((j + 1) < m && (i - 1) >= 0) {
        num_alive = num_alive + z3::ite(game_matrix[(i - 1) * m + (j + 1)] == 1, c.int_val(1), c.int_val(0));
    }
    if ((j + 1) < m && (i + 1) < n) {
        num_alive = num_alive + z3::ite(game_matrix[(i + 1) * m + (j + 1)] == 1, c.int_val(1), c.int_val(0));
    }

    return num_alive;
}

// Função para ler a matriz original
std::vector<int> read_matrix(int n, int m) {
    std::vector<int> mat(n * m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            std::cin >> mat[(i * m) + j];
        }
    return mat;
}

// Função para imprimir a matriz
void print_matrix(const std::vector<int>& mat, int n, int m) {
    std::cout << "N: " << n << " M: " << m << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << mat[(i * m) + j] << " ";
        }
        std::cout << std::endl;
    }
}

// Função para criar as variáveis do Z3
z3::expr_vector create_variables(z3::context& c, int n, int m) {
    z3::expr_vector vars(c);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            vars.push_back(c.int_const(("X" + std::to_string((i * m) + j)).c_str()));
        }
    return vars;
}

// Função para adicionar o domínio das variáveis
void add_domain_constraints(z3::optimize& solver, const z3::expr_vector& vars, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            solver.add(vars[(i * m) + j] == 0 || vars[(i * m) + j] == 1);
        }
}

// Função para adicionar restrições ao solver
void add_restrictions(z3::optimize& solver, z3::context& c, const z3::expr_vector& vars, const std::vector<int>& mat_og, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            z3::expr num_alive = alive_neighbors(c, vars, i, j, n, m);
            
            solver.add(z3::implies(c.int_val(mat_og[(i * m) + j]) == 1, 
                ((vars[(i * m) + j] == 1 && (num_alive == 3 || num_alive == 2)) || 
                 (vars[(i * m) + j] == 0 && num_alive == 3))));
            solver.add(z3::implies(c.int_val(mat_og[(i * m) + j]) == 0, 
                ((vars[(i * m) + j] == 0 && num_alive != 3) || 
                 (vars[(i * m) + j] == 1 && num_alive != 2 && num_alive != 3))));
        }
}

// Função para adicionar a função objetivo
void add_objective(z3::optimize& solver, z3::context& c, const z3::expr_vector& vars, int n, int m) {
    z3::expr cell_alive = c.int_val(0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cell_alive = cell_alive + vars[(i * m) + j];
        }
    solver.minimize(cell_alive);
}

// Função para imprimir a solução
void print_solution(const z3::model& mod, const z3::expr_vector& vars, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << mod.eval(vars[i * m + j]) << " ";
        }
        std::cout << std::endl;
    }
}