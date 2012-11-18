/*
 * Jordan Harmel
 * Vladimir Tsoy
 * Nov. 15, 2012
 *
 * CS 470 : Traveling Salesperson
 *
 */
 
#include "tsp.h"

FILE *file;

int tour_finder(tour *curr_tour);
int feasible(tour *curr_tour, struct Edge *next, int city);
int tokenize_line(char *input);
void add_city(tour *curr_tour, int city);
void remove_last_city(tour *curr_tour, int last_city);
static int num_cities = 0;
struct Edge **edges_list;

int main(int argc, char * argv[]) {
    tour best_tour;
    struct Stack *stack = createStack();
    char line[64];
    file = fopen( argv[1], "rt");
    
    while(fgets(line, 64, file) != NULL) {
        sscanf(line, "%s", &line);
        tokenize_line(line);
    }
        /*for (int i = 0; i < num_cities; ++i) {
            while(edges_list[i]->next!=NULL) {
                printf("i: %d City: %d Cost: %d\n", i, edges_list[i]->city, edges_list[i]->cost);
                edges_list[i] = edges_list[i]->next;
            }
        }*/
        int stack_size = 0;
        for (int i = 0; stack_size < num_cities; i++) {
            struct Edge **temp = malloc(sizeof(edges_list));
            while(temp[i]->next!=NULL) {
                stack_size++;
                tour *t = (tour *)malloc(sizeof(tour));
                t->cost = temp[i]->cost;
                t->count++;
                t->last_city = temp[i]->city;
                t->path= (int *)malloc(sizeof(int)*(num_cities+1));
                t->path[temp[i]->city] = temp[i]->city;
                t->path[i] = i;
                push(stack, (void *)t);
                temp[i] = temp[i]->next;
            }
        }
    fclose(file);
    //after list is built
    #pragma omp parallel num_threads(num_cities)
    {
    tour_finder((tour *)popBusyWait(stack));
    }
    
    return 0;
}

int tour_finder(tour *curr_tour) {
    int my_rank = omp_get_thread_num();
    struct Stack *my_stack = createStack();
    //print debugging stuff
    push(my_stack, (void *)curr_tour);
    tour *d = (int*)popBusyWait(my_stack);
    
    while(!empty(my_stack)) {
        curr_tour = (tour *)popBusyWait(my_stack);
        if(curr_tour->count == num_cities) {
            //if(best_tour(curr_tour)) update_best_tour(curr_tour);
        }
        else {
            for(int city = num_cities-1; city >= 1; city--){
                if(feasible(curr_tour, edges_list[curr_tour->last_city], city)){
                    int last_city = curr_tour->last_city;
                    add_city(curr_tour, city);
                    push(my_stack, curr_tour);
                    remove_last_city(curr_tour, last_city);
                }
            }
        free(curr_tour);
        }
    }
    
    return 0;
}

int feasible(tour *curr_tour, struct Edge *next, int city) {
    if(curr_tour->count == num_cities){
        //if there is an edge that points to 0 add 0, and the cost to get
        //to it and return true
        //otherwise return false
    }
    //else if(are there duplicates)
        //if yes, return false
    //else return true
    return 0;
}
void add_city(tour *curr_tour, int city){
    curr_tour->path[city] = city;
    curr_tour->last_city = city;
    
}

void remove_last_city(tour *curr_tour, int last_city){
    curr_tour->path[last_city] = -1;
    curr_tour->last_city = last_city;
}
int tokenize_line(char *input) {
    char *delims = "( ,\r\n\0)";
    
    if (atoi(input) > 0) {
        num_cities = atoi(input);
        if ( num_cities > 0) {
            edges_list = (struct Edge **)malloc(sizeof(struct Edge*) * num_cities );
            for (int i = 0; i < num_cities; ++i) {
                edges_list[i] = (struct Edge *)malloc(sizeof(struct Edge));
                edges_list[i]->city = -1;
                edges_list[i]->cost = -1;
                edges_list[i]->next = NULL;
            }
        }
        return 1;
    }
    else {
        int city_origin = atoi(strtok(input,delims));
        int city_dest = atoi(strtok(NULL, delims));
        int cost = atoi(strtok(NULL, delims));
        printf("%d %d %d\n", city_origin, city_dest, cost);
        struct Edge *temp = (struct Edge *)malloc(sizeof(struct Edge));
        temp->city = city_dest;
        temp->cost = cost;
        temp->next = edges_list[city_origin];
        edges_list[city_origin] = temp;
        }
    return 0;
}
