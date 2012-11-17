/*
 * Jordan Harmel
 * Vladimir Tsoy
 * Nov. 15, 2012
 *
 * CS 470 : Traveling Salesperson
 *
 */

typedef struct {
    int myCity;
    struct city_node *children;
} Head;

typedef struct {
    struct Node *head;
}List;

struct List *createList();

void insert_front(int d);
void remove(int d);
