#ifndef TREE_H
#define TREE_H

typedef struct tree {
    node_t* head;
} tree_t;

typedef struct node {
    int* mat;
    int num_child;
    node_t* prev;
    node_t** next_nodes;
} node_t;

tree_t* create_tree();

node_t* create_node(int* matrix, tree_t* tree, node_t* prev, int b);

#endif