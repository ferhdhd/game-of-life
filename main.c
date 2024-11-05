#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

    int n, m;
    int *mat;

    scanf("%d %d", &n, &m);

    mat = init_matrix(n, m);
    
    read_matrix(mat, n, m);

    print_matrix(mat, n, m);

    free(mat);
    
    return 0;
}