#ifndef QUEUE_H
#define QUEUE_H

struct node;
typedef struct node node_t;

struct tree;
typedef struct tree tree_t;

typedef struct q_node {
    struct q_node* next;
    struct q_node* prev;
    node_t* node;
    int cell_alive;
} q_node_t;

typedef struct q {
    q_node_t* head;
} q_t;

q_t* init_queue ();

q_node_t* create_q_node (node_t* node, int* mat_og);

int already_visited(q_t* q, q_node_t* new_node);

void insert_queue (node_t* node, q_t* q, q_t* already_visited, int* mat_og);

node_t* pop_queue (q_t* q, q_t* mat_visited);

void remove_queue (node_t* node);

void print_queue (q_t* q);


#endif