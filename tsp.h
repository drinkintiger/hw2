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
    int count;
} tour;

struct Edge {
    int cost;
    int city;
    struct Edge *next;
};
