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
    printf("\n");
}

void copy_mat(int* mat, int* mat_aux, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            mat_aux[(i*m) + j] = mat[(i*m) + j];
    }
}

int compare_matrix(int* mat, int* mat_aux, int n, int m) {
    int equal = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (mat[(i*m) + j] != mat_aux[(i*m) + j]) {
                equal = 0;
                return equal;
            }
    }
    return equal;
}

int is_solution(int* mat, int n, int m, tree_t* tree) {
    int *mat_aux = init_matrix(n, m);
    copy_mat(mat, mat_aux, n, m); // faz uma copia da matriz a ser analisada
    //print_matrix(mat, n, m);
    // percorre a matriz para gerar sua sucessora
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Gerar comparacoes para todos os vizinhos
            int numAlive = 0;
            // vizinho da esquerda
            if ((j-1) >= 0) {
                if (mat[i*m + (j-1)] == 1) {
                    numAlive++;
                }
            }
            // vizinho da diagonal esquerda de cima
            if ((j-1) >= 0 && (i-1) >= 0) {
                if (mat[(i-1)*m + (j-1)] == 1) {
                    numAlive++;
                }
            }
            // vizinho da diagonal esquerda de baixo
            if ((j-1) >= 0 && (i+1) < n) {
                if (mat[(i+1)*m + (j-1)] == 1) {
                    numAlive++;
                }
            }
            // vizinho de cima 
            if ((i-1) >= 0) {
                if (mat[(i-1)*m + j]) {
                    numAlive++;
                }
            }
            // vizinho de baixo
            if ((i+1) < n) {
                if (mat[(i+1)*m + j]){
                    numAlive++;
                }
            }
            // vizinho da direita
            if ((j+1) < m) {
                if (mat[i*m + (j+1)]){
                    numAlive++;
                }
            }
            //vizinho da diagonal direita de cima
            if ((j+1) < m && (i-1) > 0) {
                if (mat[(i-1)*m + (j+1)]) {
                    numAlive++;
                }
            }
            // vizinho da diagonal direita de baixo
            if ((j+1) < m && (i+1) < n)
                if (mat[(i+1)*m + (j+1)]){
                    numAlive++;
                }
            
            if (mat[i*m +j] == 0 && numAlive == 3){
                mat_aux[i*m +j] = 1;
            } else if (mat[i*m +j] == 1 && (numAlive < 2 || numAlive > 3)) {
                mat_aux[i*m +j] = 0;
            }
        }
    }

    //print_matrix(mat_aux, n, m);
    int comp = compare_matrix(mat_aux, tree->head->mat, n, m);
    //printf("comp:%d\n" , comp);
    free(mat_aux);
    return comp;
}

int count_n_alive(int* mat, int i, int j, int n, int m) {
    int numAlive = 0;
    // vizinho da esquerda
    if ((j-1) >= 0) {
        if (mat[i*m + (j-1)] == 1) {
            numAlive++;
        }
    }
    // vizinho da diagonal esquerda de cima
    if ((j-1) >= 0 && (i-1) >= 0) {
        if (mat[(i-1)*m + (j-1)] == 1) {
            numAlive++;
        }
    }
    // vizinho da diagonal esquerda de baixo
    if ((j-1) >= 0 && (i+1) < n) {
        if (mat[(i+1)*m + (j-1)] == 1) {
            numAlive++;
        }
    }
    // vizinho de cima 
    if ((i-1) >= 0) {
        if (mat[(i-1)*m + j]) {
            numAlive++;
        }
    }
    // vizinho de baixo
    if ((i+1) < n) {
        if (mat[(i+1)*m + j]){
            numAlive++;
        }
    }
    // vizinho da direita
    if ((j+1) < m) {
        if (mat[i*m + (j+1)]){
            numAlive++;
        }
    }
    //vizinho da diagonal direita de cima
    if ((j+1) < m && (i-1) > 0) {
        if (mat[(i-1)*m + (j+1)]) {
            numAlive++;
        }
    }
    // vizinho da diagonal direita de baixo
    if ((j+1) < m && (i+1) < n)
        if (mat[(i+1)*m + (j+1)]){
            numAlive++;
        }
    return numAlive;
}