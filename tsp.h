#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct {
    int *path;
    int cost;
} tour;

typedef struct {
    int cost;
    int myCity;
    struct node *children;
} node;
