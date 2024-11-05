#ifndef TREE_H
#define TREE_H

struct tree {
    nodo_t* head;
};
typedef struct tree tree_t;

struct nodo {
    int* mat;
    nodo* next;
};
typedef struct nodo nodo_t;

#endif