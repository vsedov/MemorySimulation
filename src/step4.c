#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Personal headers, comment these out, if you do not use xmake
#include <log.h>
#include <step4.h>

// #include "../helper/log.c/src/log.c"
// #include "../helper/log.c/src/log.h"
// #include "./include/step4.h"
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
int get_size(struct list *pList, int *counter) {
    int i = 0;
    struct node *cur = pList->head;
    while (cur) {
        i++;
        cur = cur->next;
    }
    return i;
}

void get_counter(struct list *pList, int *counter) {
    int i = 0;
    struct node *cur = pList->head;
    while (cur) {
        i++;
        cur = cur->next;
    }
    *counter = i;
}
void head_insert(struct list *pList, int *counter, int n) {
    // insert forwards from head
    struct node *head = pList->head;
    struct node *tail = pList->tail;
    while (head->i != -1 && head->next != tail) {
        head = head->next;
    }
    if (head->i == -1) {
        head->i = n;

        pList->length = pList->length - 1;
    } else {
        do {
            head = head->next;
        } while (head->i != -1 && head->next != tail);
        if (head->i == -1) {
            head->i = n;
            pList->length = pList->length - 1;
        }
    };
    pList->left = head;
}

void tail_insert(struct list *pList, int *counter, int n) {
    // insert backwards from tail
    struct node *tail = pList->tail;
    struct node *head = pList->head;
    while (tail->i != -1 && tail->prev != head) {
        tail = tail->prev;
    }
    if (tail->i == -1) {
        tail->i = n;

        pList->length = pList->length - 1;
    } else {
        do {
            tail = tail->prev;
        } while (tail->i != -1 && tail->prev != head);
        if (tail->i == -1) {
            tail->i = n;

            pList->length = pList->length - 1;
        }
    };
    pList->right = tail;
}

int has_neg_one(struct list *pList, int *counter) {
    struct node *cur = pList->head;
    while (cur) {
        if (cur->i == -1) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

void pushInt(struct list *pList, int *counter, int i) {
    if (has_neg_one(pList, counter) == 0) {

        allocateBlock(pList, counter);
    }

    if (i % 2 == 0) {
        tail_insert(pList, counter, i);
    } else {
        head_insert(pList, counter, i);
    }
}

int count_neg_one(struct list *pList, int *counter) {
    int i = 0;
    struct node *cur = pList->head;
    while (cur != NULL) {
        if (cur->i == -1) {
            i++;
        }
        cur = cur->next;
    }
    return i;
}

void pullInt(struct list *pList, int *counter, int i) {
    // | 0 |  | 1 |  | 9 |  | 25 |  | 49 |
    // remove teh last odd value if i is odd

    if (count_neg_one(pList, counter) >= BLOCKSIZE) {
        deAllocateBlock(pList, counter);
    }
    if (i % 2 == 1) {
        // printf("removing first odd value from the head.next\n");

        // odd values pList->left != pList->head
        //

        struct node *left = pList->left;
        // printf("left->i = %d\n", left->i);

        left->i = -1;
        left = left->prev;
        pList->left = left;
        pList->length = pList->length + 1;

        if (count_neg_one(pList, counter) == BLOCKSIZE) {
            deAllocateBlock(pList, counter);
        }

    } else {

        // printf("removing first even value from the tail.prev\n");

        struct node *right = pList->right;

        right->i = -1;
        right = right->next;

        pList->right = right;
        pList->length = pList->length + 1;

        if (count_neg_one(pList, counter) == BLOCKSIZE) {
            deAllocateBlock(pList, counter);
        }
    }
};

int getSignedInt(int *n) {
    // Thaznk you for the pseudo code, made life easier
    char c;
    int flip = 0;
    *n = 0;

    scanf("%c", &c);

    if (c == EOF) {
        return 0;
    }

    if (c == '\n') {
        return 0;
    }
    if (c == '-') {
        flip = -1;
    } else if (c == '+') {
        flip = 1;
    }
    while (c != '\n' && c != ' ') {
        if (c >= '0' && c <= '9') {
            *n = *n * 10 + (c - '0');
        }
        scanf("%c", &c);
    }

    *n = *n % MAX;
    *n = flip * *n;

    // if c is a new line chracter return 0 else return 1

    if (c == '\n') {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int counter = 0, n = 0, go = 1;
    struct list myList;
    printf("initialising the list ... \n");
    initialiseList(&myList, &counter);
    printList(&myList, &counter);
    // printf("Size = %d\n", get_size(&myList, &counter));
    //
    printf("ammount of blocks allocated: %d\n", BLOCKSIZE);
    // printf("ammount of MAX values: %d\n", MAX);

    while (go) {
        go = getSignedInt(&n);

        bool push = false;
        bool pull = false;

        int size = get_size(&myList, &counter);
        if ((n > 0) && (n <= MAX)) {
            printf("pushing %d integers\n", abs(n));
            push = true;
        }
        if ((n < 0) && (n >= -MAX)) {
            printf("pulling %d integers\n", abs(n));
            pull = true;
        };

        // If your blocksize is one - then pointless pushing : specify block size
        if (BLOCKSIZE == 1) {
            printList(&myList, &counter);
            break;
        }

        int j = 0;
        while (j < abs(n)) {
            // push j and pull j values
            if (push) {
                if (count_neg_one(&myList, &counter) == 0) {
                    allocateBlock(&myList, &counter);
                }

                pushInt(&myList, &counter, j);
            }
            if (pull) {
                if ((count_neg_one(&myList, &counter) == 0) && size == 2) {
                    break;
                }
                // avoid pulling from an empty List
                if (myList.head != myList.left || myList.tail != myList.right) {
                    pullInt(&myList, &counter, j);
                }
            }
            j++;
        }
        if (push || pull) {
            printList(&myList, &counter);
        }
    }
    if ((myList.head != myList.left) || (myList.tail != myList.right)) {
        printf("removing all integers ... \n");

        while ((myList.head != myList.left) || (myList.tail != myList.right)) {
            if (myList.head != myList.left) {
                pullInt(&myList, &counter, 1);
            } else if (myList.tail != myList.right) {
                pullInt(&myList, &counter, -1);
            }
        }
        printList(&myList, &counter);
        printf("freeing head and tail ... \n");
        removeList(&myList, &counter);
        printList(&myList, &counter);
        return 0;
    }
    printList(&myList, &counter);
    printf("freeing head and tail ... \n");
    removeList(&myList, &counter);
    printList(&myList, &counter);
    return 0;
}

// // Debugging code
//
// printf("\n");
// printf("\n");
// printf("Block size: %d\n", BLOCKSIZE);
// printf("MAX: %d\n", MAX);
// printf("List length: %d\n", get_size(&myList, &counter));
// printf("Counter value: %d\n", counter);
// printf("Active negatives in list: %d\n", count_neg_one(&myList, &counter));
// printf("N = %d\n", n);
// printf("abs(n) = %d\n", abs(n));
// printf("Go = %d\n", go);
// printf("Push = %d\n", push);
// printf("Pull = %d\n", pull);
// printf("\n\n");
