/*
 * Jordan Harmel
 * Vladimir Tsoy
 * Nov. 15, 2012
 *
 * CS 470 : Traveling Salesperson
 *
 */
 
void insert_front(int d) {
    struct city_node *temp;
    
    temp = (struct city_node *)malloc(sizeof(struct city_node));
    temp->myCity = d;
    
    if (Head == NULL) {
        Head = temp;
        Head -> Next = NULL;
    }
    else {
        temp -> Next = Head;
        Head = temp;
    }
}
