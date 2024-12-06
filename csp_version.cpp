#include "z3++.h"
#include <iostream>
#include <string>

z3::expr alive_neighbors(z3::context &c, z3::expr_vector game_matrix, int i, int j, int n, int m) {
    z3::expr num_alive = c.int_val(0);

    if ((j - 1) >= 0) {
        num_alive = num_alive + z3::ite(game_matrix[i * m + (j - 1)] == c.bool_val(true), c.int_val(1), c.int_val(0));
    }
    if ((j - 1) >= 0 && (i - 1) >= 0) {
        num_alive = num_alive + z3::ite(game_matrix[(i - 1) * m + (j - 1)] == c.bool_val(true), c.int_val(1), c.int_val(0));
    }
    if ((j - 1) >= 0 && (i + 1) < n) {
        num_alive = num_alive + z3::ite(game_matrix[(i + 1) * m + (j - 1)] == c.bool_val(true), c.int_val(1), c.int_val(0));
    }
    if ((i - 1) >= 0) {
        num_alive = num_alive + z3::ite(game_matrix[(i - 1) * m + j] == c.bool_val(true), c.int_val(1), c.int_val(0));
    }
    if ((i + 1) < n) {
        num_alive = num_alive + z3::ite(game_matrix[(i + 1) * m + j] == c.bool_val(true), c.int_val(1), c.int_val(0));
    }
    if ((j + 1) < m) {
        num_alive = num_alive + z3::ite(game_matrix[i * m + (j + 1)] == c.bool_val(true), c.int_val(1), c.int_val(0));
    }
    if ((j + 1) < m && (i - 1) >= 0) {
        num_alive = num_alive + z3::ite(game_matrix[(i - 1) * m + (j + 1)] == c.bool_val(true), c.int_val(1), c.int_val(0));
    }
    if ((j + 1) < m && (i + 1) < n) {
        num_alive = num_alive + z3::ite(game_matrix[(i + 1) * m + (j + 1)] == c.bool_val(true), c.int_val(1), c.int_val(0));
    }

    return num_alive;
}

z3::expr count_alive (z3::context &c, z3::expr_vector game_matrix, int n, int m) {
    z3::expr alive = c.int_val(0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            alive = alive + z3::ite(game_matrix[(i*m) + j] == c.bool_val(true), c.int_val(1), c.int_val(0));
        }
    return alive;
}

int main() {

    int n, m;

    z3::context c;
    z3::expr_vector game_matrix(c);
    z3::solver s(c);

 
    std::cin >> n >> m;

    std::vector<int> mat_og(n*m);

    s.set("timeout", (unsigned int) 30000);

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
    std::cout << std::endl;


    // criando as variáveis
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            game_matrix.push_back(c.bool_const(("X" + std::to_string((i*m) + j)).c_str()));
    }
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            s.add(game_matrix[(i*m) + j] == c.bool_val(false) || game_matrix[(i*m) + j] == c.bool_val(true));
    }

    // restricoes
    for (int i = 1; i < n-1; i++)
        for (int j = 1; j < m-1; j++) {
            z3::expr num_alive = alive_neighbors(c, game_matrix, i, j, n, m);
            
            s.add(z3::implies(c.int_val(mat_og[(i*m) + j]) == 1, ((game_matrix[(i*m) + j] == c.bool_val(true) && (num_alive == 3 || num_alive == 2)) || (game_matrix[(i*m) + j] == c.bool_val(false) && num_alive == 3))));
            s.add(z3::implies(c.int_val(mat_og[(i*m) + j]) == 0, ((game_matrix[(i*m) + j] == c.bool_val(false) && num_alive != 3) || (game_matrix[(i*m) + j] == c.bool_val(true) && num_alive != 2 && num_alive != 3))));
        }

    if (s.check() == z3::sat) {
        z3::model mod = s.get_model();
        int lst_cost = n * m; // Inicializa com o máximo custo possível.
        int act_cost = lst_cost;

        do {
            // Atualiza o modelo e calcula o custo atual baseado nas células vivas.
            mod = s.get_model();
            act_cost = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (mod.eval(game_matrix[i * m + j]).bool_value() == Z3_L_TRUE) {
                        act_cost++;
                    }
                }
            }

            // Verifica se o custo atual é menor que o último.
            if (act_cost >= lst_cost)
                break;

            // Atualiza o último custo.
            lst_cost = act_cost;

            // Adiciona restrição para encontrar uma solução com menor custo.
            s.push(); // Salva o estado do solver.
            s.add(count_alive(c, game_matrix, n, m) < c.int_val(lst_cost));

        } while (s.check() == z3::sat);

        // Saída do melhor modelo encontrado.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mod.eval(game_matrix[i * m + j]).bool_value() == Z3_L_TRUE)
                    std::cout << 1 << " ";
                else
                    std::cout << 0 << " ";
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