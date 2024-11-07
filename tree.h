#ifndef TREE_H
#define TREE_H

typedef struct tree {
    node_t* head;
} tree_t;

typedef struct node {
    int* mat;
    int num_child;
    node* prev;
    node** next_nodes;
} node_t;


node_t* create_node();
#endif