/*
 * Jordan Harmel
 * Vladimir Tsoy
 * Nov. 15, 2012
 *
 * CS 470 : Traveling Salesperson
 *
 */
#include <stdio.h>
#include <stdlib.h>

struct city_node {
    int myCity;
    int cost;
    struct city_node *Next;
} Head;

struct List{
    struct city_node *Head;
};

struct List *createList();

void insert_front(int d, int cost,struct List *theList);
