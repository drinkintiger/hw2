/*
 * Jordan Harmel
 * Vladimir Tsoy
 * Nov. 15, 2012
 *
 * CS 470 : Traveling Salesperson
 * Partial linked list implementation.
 */
 
#include "list.h"

struct List *createStack() {
    struct List *s;
    s = (struct List *) malloc(sizeof(struct List));
    s->Head = NULL;
    return s;
}

void insert_front(int d, int cost, struct List *theList) {
    struct city_node *temp;
    
    temp = (struct city_node *)malloc(sizeof(struct city_node));
    temp->myCity = d;
    temp->cost = cost;
    
    if (theList->Head == NULL) { /* The list is empty */
        Head = *temp;
        theList->Head->Next = NULL;
    }
    else { /* The list is not empty */
        *temp -> Next = Head;
        Head = *temp;
    }
}
