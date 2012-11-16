
#include "stack.h"

struct Stack *createStack() {
    struct Stack *s;
    s = (struct Stack *) malloc(sizeof(struct Stack));
    s->top = NULL;
    omp_init_lock(&s->lock);
    return s;
}

void destroyStack(struct Stack *s) {
    struct Node *temp;
    while (s->top != NULL) {
        temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
    omp_destroy_lock(&s->lock);
    free(s);
}

void push(struct Stack *s, void *d) {
    struct Node *temp;
    temp = (struct Node *) malloc(sizeof(struct Node));
    temp->data = d;
    omp_set_lock(&s->lock);
    temp->next = s->top;
    s->top = temp;
    omp_unset_lock(&s->lock);
}

void *popBusyWait(struct Stack *s) {
    struct Node *temp;
    void *d;
    omp_set_lock(&s->lock);
    while (s->top == NULL) {
        omp_unset_lock(&s->lock);
        omp_set_lock(&s->lock);
    }
    d = s->top->data;
    temp = s->top;
    s->top = s->top->next;
    omp_unset_lock(&s->lock);
    free(temp);
    return d;
}