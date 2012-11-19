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
void add_city(tour *curr_tour, int city, int arr_ptr);
void remove_last_city(tour *curr_tour, int arr_ptr);
static int num_cities = 0;
tour best_tour;
omp_lock_t lock;
struct Edge **edges_list;

int main(int argc, char * argv[]) {
    struct Stack *stack = createStack();
    omp_init_lock(&lock);
    char line[64];
    file = fopen( argv[1], "rt");
    
    while(fgets(line, 64, file) != NULL) {
        sscanf(line, "%s", &line);
        tokenize_line(line);
    }
        int stack_size = 0;
        for (int i = 0; stack_size < num_cities; i++) {
            struct Edge **temp_list = (struct Edge **)malloc(sizeof(struct Edge*) * num_cities );
            temp_list = edges_list;
            while(temp_list[i]->next!=NULL) {
                stack_size++;
                tour *t = (tour *)malloc(sizeof(tour));
                t->cost = temp_list[i]->cost;
                t->count++;
                t->path= (int *)malloc(sizeof(int)*(num_cities+1));
                t->path[0] = i;
                t->path[1] = temp_list[i]->city;
                push(stack, (void *)t);
                temp_list[i] = temp_list[i]->next;
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
    int arr_ptr = 2;//used for the path in the tour struct
    struct Stack *my_stack = createStack();
    push(my_stack, (void *)curr_tour);
    
    while(!empty(my_stack)) {
        curr_tour = (tour *)popBusyWait(my_stack);
        if(curr_tour->count == num_cities) {
            omp_set_lock(&lock);
            //if(best_tour(curr_tour)) update_best_tour(curr_tour);
            omp_unset_lock(&lock);
        }
        else {
            for(int city = num_cities-1; city >= 1; city--){
                if(feasible(curr_tour, edges_list[curr_tour->path[arr_ptr]], city)){
                    add_city(curr_tour, city, arr_ptr);
                    push(my_stack, curr_tour);
                    remove_last_city(curr_tour, arr_ptr);
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
void add_city(tour *curr_tour, int city, int arr_ptr){
    curr_tour->path[arr_ptr] = city;
    
}

void remove_last_city(tour *curr_tour, int arr_ptr){
    curr_tour->path[arr_ptr] = -1;
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
