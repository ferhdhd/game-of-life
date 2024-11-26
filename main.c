#include "matrix.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

#define DEEPENING_LIMIT 2

int main() {

    int n, m;
    int *mat;

    scanf("%d %d", &n, &m);

    mat = init_matrix(n, m);
    
    read_matrix(mat, n, m);

    iterative_deepening(DEEPENING_LIMIT, mat, n, m);

    free(mat);
    
    return 0;
}