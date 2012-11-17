/*
 * Jordan Harmel
 * Vladimir Tsoy
 * Nov. 15, 2012
 *
 * CS 470 : Traveling Salesperson
 *
 */
#include "stack.h"
#include "list.h"

typedef struct {
    struct Node *path;
    int cost;
    int count;
} tour;
