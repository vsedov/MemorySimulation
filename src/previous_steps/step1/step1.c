#include <stdio.h>
#include <stdlib.h>

#include "step1.h"
// struct node {
//     int i;
//     struct node *next;
//     struct node *prev;
// };
//
// struct list {
//     struct node *head;
//     struct node *tail;
//     struct node *right;
//     struct node *left;
//     int length;
// };

// void *allocator(int size, int *counter);
// void deAllocator(void *p, int *counter);
// void initialiseList(struct list *pList, int *counter);

void *allocator(int size, int *counter) {
    void *p = malloc(size);
    if (p == NULL) {
        printf("Out of memory\n");
        exit(1);
    }
    (*counter)++;
    return p;
}

void deAllocator(void *p, int *counter) {
    free(p);
    (*counter)--;
}

void initialiseList(struct list *pList, int *counter) {
    pList->head = (struct node *)allocator(sizeof(struct node), counter);
    pList->tail = (struct node *)allocator(sizeof(struct node), counter);
    pList->left = pList->head;
    pList->right = pList->tail;
    pList->tail->i = 0;
    pList->head->i = 0;
    pList->head->next = pList->tail;
    pList->head->prev = NULL;
    pList->tail->prev = pList->head;
    pList->tail->next = NULL;
}

int main(int argc, char *argv[]) {

    int counter = 0;
    struct list myList;
    printf("allocating two nodes ...\n");
    printf("initialising list ...\n");
    initialiseList(&myList, &counter);

    printf(" | %d | | %d | \n", myList.head->i, myList.tail->i);
    printf("counter = %d\n", counter);
    printf("freeing the list ...\n");
    deAllocator(myList.head, &counter);
    deAllocator(myList.tail, &counter);
    printf("counter = %d\n", counter);
    return 0;
}
