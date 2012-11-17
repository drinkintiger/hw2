/*
 * Jordan Harmel
 * Vladimir Tsoy
 * Nov. 15, 2012
 *
 * CS 470 : Traveling Salesperson
 *
 */
#include "stack.h"
#include <string.h>

typedef struct {
    struct node *path;
    int cost;
    int count;
} tour;
