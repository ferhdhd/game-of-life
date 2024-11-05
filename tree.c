#include "tree.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

tree_t* create_tree(){
    tree_t* new_tree = malloc(sizeof(tree_t));
    return new_tree;
}

void insert_nodo (int* matrix){
    nodo_t* new_nodo = malloc(sizeof(nodo_t));
    new_nodo->mat = matrix;
    new_nodo->next = NULL; 
}