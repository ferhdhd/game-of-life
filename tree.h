#ifndef TREE_H
#define TREE_H

#include "queue.h"

typedef struct node {
    int* mat;
    int n;
    int m;
    int num_child;
    struct node* prev;
    struct node** next_nodes;
} node_t;

typedef struct tree {
    node_t* head;
} tree_t;

tree_t* create_tree();

node_t* create_node(int* matrix, tree_t* tree, node_t* prev, int n, int m);

void free_node(node_t* node);

void free_tree(tree_t* tree);

void expand(node_t* node, tree_t* tree, q_t* queue, q_t* mat_visited);

int dfs_limited(tree_t* tree, node_t* node, int depth, int limit);

int iterative_deepening (int max_depth, int* mat, int n, int m);

int count_alive_cells(int* mat, int n, int m);

node_t* select_best_child(node_t* node, tree_t* tree);

int h(int* mat_og, int* new_mat, int n, int m);

int greedy_search(tree_t* tree, node_t* node, q_t* queue, q_t* mat_visited);

int greedy_algorithm(int* mat, int n, int m);

#endif