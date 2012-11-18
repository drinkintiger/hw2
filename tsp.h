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
    int last_city;
} tour;

struct Edge {
    int city;
    int cost;
    struct Edge *next;
};
