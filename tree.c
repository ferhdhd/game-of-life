#include "tree.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

tree_t* create_tree(){
    tree_t* new_tree = malloc(sizeof(tree_t));
    new_tree->head = NULL;
    
    return new_tree;
}

node_t* create_node(int* matrix, tree_t* tree, node_t* prev, int b) {
    node_t* new_node = malloc(sizeof(node_t));

    if (tree->head == NULL) {
        tree->head = new_node;
    } else {
        new_node->prev = prev;
        prev->next_nodes[prev->num_child] = new_node;
        prev->num_child++;
    }
    new_node->num_child = 0;
    new_node->mat = matrix;
    new_node->next_nodes = malloc(sizeof(node_t) * b);

    return new_node;
}