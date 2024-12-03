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

q_node_t* create_q_node (node_t* node, int* mat_og) {
    q_node_t* q_node = malloc(sizeof(q_node_t));

    q_node->next = NULL;
    q_node->node = node;
    q_node->cell_alive = h(mat_og, node->mat, node->n, node->m);

    return q_node;
}

void insert_queue (node_t* node, q_t* q, int* mat_og) {
    q_node_t* new_node = create_q_node(node, mat_og);

    if (q->head == NULL || q->head->cell_alive >= new_node->cell_alive) {
        new_node->next = q->head;
        q->head = new_node;
        return;
    }   

    q_node_t* current = q->head;
    while (current->next != NULL && current->next->cell_alive < new_node->cell_alive) {
        if (compare_matrix(node->mat, current->node->mat, node->n, node->m)) // nodo repetido
            return;
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

node_t* pop_queue (q_t* q) {
    node_t* aux = q->head->node;
    q_node_t* aux_q = q->head->next;
    free(q->head);

    q->head = aux_q;

    return aux;
}

void print_queue (q_t* q) {
    q_node_t* current = q->head;
    int i = 1;

    do {
        printf("num fila: %d\n" , i);
        printf("qtd vivos: %d\n" , current->cell_alive);
        print_matrix(current->node->mat, current->node->n, current->node->m);
        i++;
        current = current->next;
    } while (current != NULL);
}
