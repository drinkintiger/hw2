
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

struct Stack {
    struct Node *top;
    omp_lock_t lock;
};

struct Node {
    void * data;
    struct Node *next;
};

struct Stack *createStack();

void destroyStack(struct Stack *s);

void push(struct Stack *s, void *d);

void *popBusyWait(struct Stack *s) ;