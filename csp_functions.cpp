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
