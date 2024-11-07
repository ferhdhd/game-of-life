#include "matrix.h"
#include "tree.h"
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

void copy_mat(int* mat, int* mat_aux, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            mat_aux[(i*m) + j] = mat[(i*m) + j];
    }
}

int is_solution(int* mat, int n, int m, tree_t* tree) {
    int *mat_aux = init_matrix(n, m);
    copy_mat(mat_aux, mat, n, m); // faz uma copia da matriz a ser analisada

    // percorre a matriz para gerar sua sucessora
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Gerar comparacoes para todos os vizinhos
            int numAlive = 0;
            if (mat_aux)    
            
        }
    }

    free(mat_aux);
    
}