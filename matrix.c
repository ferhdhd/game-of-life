#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

int* init_matrix(int n, int m) {
    int *mat = malloc(n * m * sizeof(int));

    return mat;
}

void read_matrix(int* mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            scanf("%d", &mat[(i*m) + j]);
    }
}

void print_matrix(int* mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", mat[(i*m) + j]);
        printf("\n");
    }
}