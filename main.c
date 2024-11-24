#include "matrix.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

    int n, m;
    int *mat, *mat_aux;
    //tree_t* tree = create_tree();

    scanf("%d %d", &n, &m);

    mat = init_matrix(n, m);
    mat_aux = init_matrix(n, m);
    
    read_matrix(mat, n, m);
    read_matrix(mat_aux, n, m);

    iterative_deepening(2, mat, n, m);

    /*
    node_t* node = create_node(mat, tree, NULL, n*m);

    print_matrix(mat_aux, n, m);

    
    if (is_solution(mat_aux, n, m,tree))
        printf("E SOLUCAO\n");
    else
        printf("NAO E SOLUCAO\n");

    free(mat);
    */
    
    return 0;
}