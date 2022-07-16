#ifndef STEP_H
#include <stdlib.h>
#define STEP_H
#define VERSION "0.1.0"

// This can be changed
#define BLOCKSIZE 3

struct node {
    int i;
    struct node *next;
    struct node *prev;
};

struct list {
    struct node *head;
    struct node *tail;
    struct node *right;
    struct node *left;
    size_t length;
};
void printList(struct list *pList, int *counter);

void *allocator(int size, int *counter);

void deAllocator(void *p, int *counter);

void initialiseList(struct list *pList, int *counter);

void removeList(struct list *pList, int *counter);

void deAllocateBlock(struct list *pList, int *counter);

void allocateBlock(struct list *pList, int *counter);

#endif
