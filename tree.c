#include "tree.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

tree_t* create_tree() {
    tree_t* new_tree = malloc(sizeof(tree_t));
    new_tree->head = NULL;
    
    return new_tree;
}

node_t* create_node(int* matrix, tree_t* tree, node_t* prev, int n, int m) {
    node_t* new_node = malloc(sizeof(node_t));
    new_node->next_nodes = malloc(sizeof(node_t) * (n*m));

    if (tree->head == NULL) {
        tree->head = new_node;
    } else {
        new_node->prev = prev;
        prev->next_nodes[prev->num_child] = new_node;
        prev->num_child++;
    }
    new_node->num_child = n*m;
    new_node->mat = matrix;
    new_node->n = n;
    new_node->m = m;

    return new_node;
}

void free_node(node_t* node) {
    if (node == NULL) 
        return;

    for (int i = 0; i < node->num_child; i++) {
        if (node->next_nodes[i]) {
            free_node(node->next_nodes[i]);
            node->next_nodes[i] = NULL;
        }    
    }

    free(node->mat);
    free(node->next_nodes);
    free(node);
}

void free_tree(tree_t* tree) {
    if (tree == NULL) return;
    free_node(tree->head);
    free(tree);
}

void flip_num(int* mat, int i) {
    if (mat[i] == 0)
        mat[i] = 1;
    else
        mat[i] = 0;
}

void expand(node_t* node, tree_t* tree) {
    printf("CHEGA AQUI");
    for (int i = 0; i < node->num_child; i++) {
        node->next_nodes[i] = create_node(node->mat, tree, node, node->n, node->m);
        flip_num(node->next_nodes[i]->mat, i);
    }
}

int dfs_limited(tree_t* tree, node_t* node, int depth, int limit) {
    printf("CHEGA DFS\n");

    if (depth > limit)
        return 0;

    if (is_solution(node->mat, node->n, node->m, tree)) {
        printf("ENTRA IF\n");
        print_matrix(node->mat, node->n, node->m);
        return 1;
    }
    
    printf("CHEGA EXPAND");
    expand(node, tree);

    for (int i = 0; i < node->num_child; i++) {
        node_t *child = node->next_nodes[i];

        if (child != node->prev) {
            if (dfs_limited(tree, child, depth+1, limit))
                return 1;
        } 
    }
    //free_node(node);
    return 0;
}

int iterative_deepening (int max_depth, int* mat, int n, int m) {
    for (int limit = 0; limit <= max_depth; limit++) {
        printf("ITERACAO %d \n", limit);
        tree_t* tree = create_tree();
        node_t* root_node = create_node(mat, tree, NULL, n, m);
        tree->head = root_node;
        if (dfs_limited(tree, root_node, 0, limit)) {
            printf("AIAI \n");
            free_tree(tree);
            printf("AI \n");
            return 1;
        }
        free_tree(tree);
    }
    return 0;
}