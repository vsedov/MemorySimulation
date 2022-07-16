#include <stdio.h>
#include <stdlib.h>

#include "step2.h"

void printList(struct list *pList, int *counter) {
    if (pList->head) {
        struct node *cur = pList->head;
        while (cur) {
            printf(" | %d | ", cur->i);
            cur = cur->next;
        }
        printf("\n");
    }
    printf("counter = %d\n", *counter);
}
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

void removeList(struct list *pList, int *counter) {
    deAllocator(pList->head, counter);
    deAllocator(pList->tail, counter);
    pList->head = NULL;
    pList->tail = NULL;
    pList->length = 0;
    pList->left = NULL;
    pList->right = NULL;
}
void deAllocateBlock(struct list *pList, int *counter) {
    int i = 0;
    while (i < BLOCKSIZE) {
        struct node *temp = pList->left->next;
        pList->left->next->next->prev = pList->left;
        pList->left->next = pList->left->next->next;
        deAllocator(temp, counter);
        pList->length = pList->length - 1;
        i++;
    }
}

void allocateBlock(struct list *pList, int *counter) {
    int i = 0;
    while (i < BLOCKSIZE) {
        struct node *temp = (struct node *)allocator(sizeof(struct node), counter);
        temp->i = -1;
        temp->next = pList->left->next;
        temp->prev = pList->left;
        pList->left->next->prev = temp;
        pList->left->next = temp;
        pList->length = pList->length + 1;
        i++;
    }
}

int main() {
    int counter = 0;
    struct list myList;
    printf("initialising the list ... \n");
    initialiseList(&myList, &counter);
    printList(&myList, &counter);
    printf("allocating %d free nodes ... \n", BLOCKSIZE);
    allocateBlock(&myList, &counter);
    printList(&myList, &counter);

    printf("freeing %d free nodes ... \n", BLOCKSIZE);
    deAllocateBlock(&myList, &counter);
    printList(&myList, &counter);
    printf("freeing head and tail ... \n");
    removeList(&myList, &counter);
    printList(&myList, &counter);
}

// int main(int argc, char *argv[]) {
//
//   int counter = 0;
//   struct list myList;
//   printf("allocating two nodes ...\n");
//   printf("initialising list ...\n");
//   initialiseList(&myList, &counter);
//
//   printf(" | %d | | %d | \n", myList.head->i, myList.tail->i);
//   printf("counter = %d\n", counter);
//   printf("freeing the list ...\n");
//   deAllocator(myList.head, &counter);
//   deAllocator(myList.tail, &counter);
//   printf("counter = %d\n", counter);
//   return 0;
// }
