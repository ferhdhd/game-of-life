#include "matrix.h"
#include "tree.h"
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

void expand(node_t* node, tree_t* tree, q_t* queue, q_t* mat_visited) {
    for (int i = 0; i < node->num_child; i++) {
        node->next_nodes[i] = create_node(node->mat, tree, node, node->n, node->m);
        flip_num(node->next_nodes[i]->mat, i);
        insert_queue(node->next_nodes[i], queue, mat_visited, tree->head->mat);
    }
}

/*int dfs_limited(tree_t* tree, node_t* node, int depth, int limit) {
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
} */

int count_alive_cells(int* mat, int n, int m) {
    int count = 0;
    for (int i = 0; i < n * m; i++) {
        if (mat[i] == 1) count++;
    }
    return count;
}

node_t* select_best_child(node_t* node, tree_t* tree) {
    int min_alive = __INT_MAX__;
    node_t* best_child = NULL;

    for (int i = 0; i < node->num_child; i++) {
        node_t* child = node->next_nodes[i];
        if (child != node->prev) { 
            int alive_cells = count_alive_cells(child->mat, child->n, child->m);
            if (alive_cells < min_alive) {
                min_alive = alive_cells;
                best_child = child;
            }
        }
    }

    return best_child;
}

int h(int* mat_og, int* new_mat, int n, int m) {
    int cont = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int numAlive = count_n_alive(new_mat, i, j, n, m);
            if (mat_og[(i*m) + j] == 1) { // caso onde a celula original eh viva
                if (new_mat[(i*m) + j] == 0 && numAlive != 3) // caso onde a anterior eh morta e não tem 3 vizinhos vivos (muito penalizada)
                    cont+= 4;
                else if (new_mat[(i*m) + j] == 1 && (numAlive == 2 || numAlive == 3)) // anterior eh viva e tem 2 ou 3 vizinhos vivos (pouco penalizada)
                    cont += 3;
                else if (new_mat[(i*m) + j] == 1 && (numAlive != 2 || numAlive != 3)) // anterior eh viva e tem menos de 2 vizinhos vivos ou mais de 3
                    cont += 4;                                                        // (pouco penalizado)
            } else { // caso onde celula original e morta
                if (new_mat[(i*m) + j] == 0) { // anterior e morta
                    if (numAlive == 3) // possui 3 vizinhos vivos (muito penalisado)
                        cont+= 4;
                } else { // anterior eh viva
                    if (numAlive == 2 || numAlive == 3) // possui 2 ou 3 vizinhos vivos (muito penalizado)
                        cont+= 4;
                    else if (numAlive != 2 || numAlive != 3) // possui menos de 2 ou mais de 3 vizinhos vivos (pouco penalisado)
                        cont+= 3;
                }
            }
        }
    return cont;
}

int greedy_search(tree_t* tree, node_t* node, q_t* queue, q_t* mat_visited) {
    //while (1) {
    for (int i = 0; i < 10000; i++) {
        //printf("NODO ATUAL\n");
        //print_matrix(node->mat, node->n, node->m);
        //printf("\n");
        printf("Iteracao: %d\n" , i);
        if (is_solution(node->mat, node->n, node->m, tree)) {
            printf("Iteracao: %d\n" , i);
            printf("Solução encontrada:\n");
            print_matrix(node->mat, node->n, node->m);
            return 1;
        }

        expand(node, tree, queue, mat_visited);
        //print_queue(queue);
        node_t* best_child = pop_queue(queue, mat_visited);

        if (!best_child) {
            printf("Nenhum filho válido encontrado.\n");
            return 0;
        }

        node = best_child; 
    }

    return 0;
}

int greedy_algorithm(int* mat, int n, int m) {
    tree_t* tree = create_tree();
    node_t* root_node = create_node(mat, tree, NULL, n, m);
    q_t* queue = init_queue();
    q_t* mat_visited = init_queue();
    tree->head = root_node;

    return greedy_search(tree, root_node, queue, mat_visited);  
}
