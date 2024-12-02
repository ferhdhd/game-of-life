#include "queue.h"
#include "tree.h"
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

q_t* init_queue () {
    q_t* q = malloc(sizeof(q_t));

    q->head = NULL;

    return q;
}

q_node_t* create_q_node (node_t* node) {
    q_node_t* q_node = malloc(sizeof(q_node_t));

    q_node->next = NULL;
    q_node->node = node;
    q_node->cell_alive = count_alive_cells(node->mat, node->n, node->m);

    return q_node;
}

void insert_queue (node_t* node, q_t* q) {
    q_node_t* new_node = create_q_node(node);

    if (q->head == NULL || q->head->cell_alive >= new_node->cell_alive) {
        new_node->next = q->head;
        q->head = new_node;
        print_matrix(node->mat, node->n, node->m);
        return;
    }   

    q_node_t* current = q->head;
    while (current->next != NULL && current->next->cell_alive < new_node->cell_alive) {
        if (compare_matrix(node->mat, current->node->mat, node->n, node->m)) // nodo repetido
            return;
        current = current->next;
    }

    print_matrix(node->mat, node->n, node->m);
    new_node->next = current->next;
    current->next = new_node;
}

node_t* pop_queue (q_t* q) {
    node_t* aux = q->head->node;
    free(q->head);

    q->head = q->head->next;

    return aux;
}
