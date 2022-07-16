#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// -- Change these to what ever is required ---

/** @BLOCKSIZE */
#define BLOCKSIZE 10

/** @MAX */
#define MAX 10

/**
 * Node of next and prev  pointers
 */
struct node {
    int i;
    struct node *next;
    struct node *prev;
};

/**
 * Struct List is a linked list of nodes
 * with a head and tail pointer.
 * The head pointer is the first node
 *
 */
struct list {
    struct node *head;
    struct node *tail;
    struct node *right;
    struct node *left;
    size_t length;
};
/**
 * @brief Prints the list in a human readable format
 *
 * @param pList The list to print
 * @param counter The counter to print
 */
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
/**
 * @brief allocates memory for a new node
 *
 * @param size The size of the node
 * @param counter The counter to print
 * @return struct node* The new node
 */
void *allocator(int size, int *counter) {
    void *p = malloc(size);
    if (p == NULL) {
        printf("Out of memory\n");
        exit(1);
    }
    (*counter)++;

    return p;
}

/**
 * @brief deallocates memory for a node
 *
 * @param p The node to deallocate
 * @param counter The counter to print
 */
void deAllocator(void *p, int *counter) {
    free(p);
    (*counter)--;
}

/**
 * @brief initializes a new list
 *
 * @param pList The list to initialize
 * @param counter The counter within allocator and deallocator
 */
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

/**
 * @brief Removes tail and head from teh list
 *
 * @param pList The list to remove from
 * @param counter The counter within allocator and deallocator
 */
void removeList(struct list *pList, int *counter) {
    deAllocator(pList->head, counter);
    deAllocator(pList->tail, counter);
    pList->head = NULL;
    pList->tail = NULL;
    pList->length = 0;
    pList->left = NULL;
    pList->right = NULL;
}
/**
 * @brief Deallocates Blocksize from the list
 *
 * @param pList  The list to deallocate from
 * @param counter The counter within allocator and deallocator
 */
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

/**
 * @brief Allocates Blocksize from the list
 *
 * @param pList The list to allocate from
 * @param counter The counter within allocator and deallocator
 */
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
/**
 * @brief Get size of the current list
 *
 * @param pList The list to get the size of
 * @param counter
 * @return
 */
int get_size(struct list *pList, int *counter) {
    int i = 0;
    struct node *cur = pList->head;
    while (cur) {
        i++;
        cur = cur->next;
    }
    return i;
}

/**
 * @brief Get counter value
 *
 * @param pList
 * @param counter
 */
void get_counter(struct list *pList, int *counter) {
    int i = 0;
    struct node *cur = pList->head;
    while (cur) {
        i++;
        cur = cur->next;
    }
    *counter = i;
}
/**
 * @brief Insert into head, where | x | y | z | --> you insert from z to right
 *
 * @param pList
 * @param counter
 * @param n
 */
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

/**
 * @brief insert into tail from x | z | y where you insert from x moving left
 *
 * @param pList
 * @param counter
 * @param n
 */
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

/**
 * @brief Check if there are free allocations, -1 = free space
 *
 * @param pList
 * @param counter
 * @return
 */
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

/**
 * @brief Call allocate block if there is no zeros - otherweise check
 * for the list : if i % 2 == -1  then insert at head else instert at tail @tail_insert
 *
 * @param pList
 * @param counter
 * @param i
 */
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

/**
 * @brief deallocate or removes info from the list ; freeing up space by using -1
 *  -1 = free space :  if i % 2 == 1 then left.i  will be repplaced with -1 and same with the tail end
 *
 * @param pList
 * @param counter
 * @param i
 */
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
}

/**
 * @brief getSignedInt from user input using scanf("%d")
 *
 * checks if there is a positive or negative number and returns a // odd values pList->left != pList->head and even
 * values pList->right != pList->tail
 *
 * @param n
 * @return
 */
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

/**
 * @brief main function :
 *
 * @return
 */
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
            // printList(&myList, &counter);
            break;
        }

        int j = 0;
        while (j < abs(n)) {
            // push j and pull j values
            if (push) {

                // Nothign there to be pushed, allocation of block is required
                if (count_neg_one(&myList, &counter) == 0) {
                    allocateBlock(&myList, &counter);
                }

                pushInt(&myList, &counter, j);
            }
            if (pull) {
                // You cant pull if there is no free spaces and that the size is only tail and head
                if ((count_neg_one(&myList, &counter) == 0) && size == 2) {
                    break;
                }

                // Only pull if the pointers of head does not = left and tail does not = right
                //  Otherwise this will pillInt 0 | 0 to 0 | -1
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
