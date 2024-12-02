#ifndef QUEUE_H
#define QUEUE_H

struct node;
typedef struct node node_t;

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

q_node_t* create_q_node (node_t* node);

void insert_queue (node_t* node, q_t* q);

node_t* pop_queue (q_t* q);

void remove_queue (node_t* node);


#endif