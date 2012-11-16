/*
 * Jordan Harmel
 * Vladimir Tsoy
 * Nov. 15, 2012
 *
 * CS 470 : Traveling Salesperson
 *
 */
#include "stack.h"

typedef struct {
    int *path;
    int cost;
} tour;

typedef struct {
    int myCity;
    struct node *children;
} node;
