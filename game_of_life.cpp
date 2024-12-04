#include "csp_functions.hpp"

int main() {

    int n, m;

    z3::context c;
    z3::expr_vector game_matrix(c);
    z3::optimize s(c);
 
    std::cin >> n >> m;

    std::vector<int> mat_og(n*m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            std::cin >> mat_og[(i*m) + j];
        }
    
    std::cout << "N: " << n << " M: " << m << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << mat_og[(i*m) + j] << " ";
        }
        std::cout << std::endl;
    }

    // criando as variáveis
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            game_matrix.push_back(c.int_const(("X" + std::to_string((i*m) + j)).c_str()));
    }

    // criando o dominio
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            s.add(game_matrix[(i*m) + j] == 0 || game_matrix[(i*m) + j] == 1);
    }

    // restricoes
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            z3::expr num_alive = alive_neighbors(c, game_matrix, i, j, n, m);
            
            s.add(z3::implies(c.int_val(mat_og[(i*m) + j]) == 1, ((game_matrix[(i*m) + j] == 1 && (num_alive == 3 || num_alive == 2)) || (game_matrix[(i*m) + j] == 0 && num_alive == 3))));
            s.add(z3::implies(c.int_val(mat_og[(i*m) + j]) == 0, ((game_matrix[(i*m) + j] == 0 && num_alive != 3) || (game_matrix[(i*m) + j] == 1 && num_alive != 2 && num_alive != 3))));
        }

    // funcao a minimizar
    z3::expr cell_alive = c.int_val(0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cell_alive = cell_alive + game_matrix[(i*m) + j];
    }
    s.minimize(cell_alive);

    if (s.check() == z3::sat) {
        std::cout << "Solução encontrada" << std::endl;
        z3::model mod = s.get_model();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << mod.eval(game_matrix[i*m + j]) << " ";
            }
            std::cout << std::endl;
        }

    } else {
        std::cout << "Nenhuma solução encontrada." << std::endl;
    }
    
    
    /*std::cout << "Conteúdo do expr_vector:" << std::endl;
    for (unsigned i = 0; i < game_matrix.size(); i++) {
        std::cout << game_matrix[i] << std::endl;
    } */

    return 0;
}

