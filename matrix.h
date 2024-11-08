#ifndef MATRIX_H
#define MATRIX_H

#include "tree.h"

int* init_matrix(int n, int m);

void read_matrix(int* mat, int n, int m);

void print_matrix(int* mat, int n, int m);

void copy_mat(int* mat, int* mat_aux, int n, int m);

int compare_matrix(int* mat, int* mat_aux, int n, int m);

int is_solution(int* mat, int n, int m, tree_t* tree);

#endif