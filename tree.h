#ifndef TREE_H
#define TREE_H


typedef struct node {
    int* mat;
    int num_child;
    struct node* prev;
    struct node** next_nodes;
} node_t;

typedef struct tree {
    node_t* head;
} tree_t;

tree_t* create_tree();

node_t* create_node(int* matrix, tree_t* tree, node_t* prev, int b);

#endif