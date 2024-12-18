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
    for (int i = 0; i < (n*m); i++) {
        new_node->next_nodes[i] = NULL;
    }
    new_node->mat = malloc(sizeof(int) * (n*m));

    if (tree->head == NULL) {
        tree->head = new_node;
        new_node->prev = NULL;
    } else {
        new_node->prev = prev;
    }
    new_node->num_child = n*m;
    copy_mat(matrix, new_node->mat, n, m);
    new_node->n = n;
    new_node->m = m;

    return new_node;
}

void free_node(node_t* node) {
    if (node == NULL) 
        return;

    for (int i = 0; i < node->num_child; i++) {
        if (node->next_nodes[i]) {
            //printf("i:%d , problema aqui?\n" , i);
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
    tree = NULL;
}

void flip_num(int* mat, int i) {
    if (mat[i] == 0)
        mat[i] = 1;
    else
        mat[i] = 0;
}

void expand(node_t* node, tree_t* tree) {
    //printf("CHEGA AQUI\n");
    for (int i = 0; i < node->num_child; i++) {
        //printf("num_child: %d\n e i:%d", node->num_child, i);
        node->next_nodes[i] = create_node(node->mat, tree, node, node->n, node->m);
        flip_num(node->next_nodes[i]->mat, i);
        //print_matrix(node->next_nodes[i]->mat, node->n, node->m);
    }
}

int dfs_limited(tree_t* tree, node_t* node, int depth, int limit) {
    //printf("CHEGA DFS\n");

    if (depth > limit)
        return 0;

    if (is_solution(node->mat, node->n, node->m, tree)) {
        printf("SOLUCAO\n");
        print_matrix(node->mat, node->n, node->m);
        return 1;
    }
    
    //printf("CHEGA EXPAND\n");
    expand(node, tree);

    for (int i = 0; i < node->num_child; i++) {
        node_t *child = node->next_nodes[i];

        if (child != node->prev) {
            if (dfs_limited(tree, child, depth+1, limit))
                return 1;
        } 
    }
    
    return 0;
}

int iterative_deepening (int max_depth, int* mat, int n, int m) {
    for (int limit = 0; limit <= max_depth; limit++) {
        //printf("ITERACAO %d \n", limit);
        tree_t* tree = create_tree();
        node_t* root_node = create_node(mat, tree, NULL, n, m);
        tree->head = root_node;
        if (dfs_limited(tree, root_node, 0, limit)) {
            //printf("AIAI \n");
            free_tree(tree);
            //printf("AI \n");
            return 1;
        }
        free_tree(tree);
    }
    return 0;
}