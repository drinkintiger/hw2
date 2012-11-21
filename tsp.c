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
int feasible(tour *curr_tour,  Edge *next);
int tokenize_line(char *input);
tour *add_city(tour *curr_tour, Edge *next);
void remove_last_city(tour *curr_tour);
static int num_cities = 0;
omp_lock_t lock;
Edge **edges_list;
tour best_tour;
int thds = 0;

int main(int argc, char * argv[]) {
    struct Stack *stack = createStack();
    omp_init_lock(&lock);
    char line[64];
    file = fopen( argv[1], "rt");
    best_tour.cost = 2232323;
    while(fgets(line, 64, file) != NULL) {
        sscanf(line, "%s", &line);
        tokenize_line(line);
    }
            
            Edge *ptr = edges_list[0];
            while(ptr != NULL) {
                thds++;
                tour *t = (tour *)malloc(sizeof(tour));
                t->cost = ptr->cost;
                t->count = 2;
                t->path= (int *)malloc(sizeof(int)*(num_cities+1));
                t->path[0] = 0;
                t->path[1] = ptr->city;
                push(stack, (void *)t);
                ptr = ptr->next;
            }
    fclose(file);
    
    #pragma omp parallel num_threads(thds) default(shared)
    {
        tour_finder( (tour *)popBusyWait(stack) );
    }
    
    for (int i = 0; i < best_tour.count; i++) {
        printf("%d ", best_tour.path[i]);
    }
    printf("\nBest tour cost was %d\n", best_tour.cost);
    return 0;
}

int tour_finder(tour *curr_tour) {
    struct Stack *my_stack = createStack();
    push(my_stack, (void *)curr_tour);
    while(!empty(my_stack)) {
        curr_tour = (tour *)popBusyWait(my_stack);
        if(curr_tour->count == num_cities + 1) {
            omp_set_lock(&lock);
            if( (curr_tour->cost) < (best_tour.cost) ) {
                best_tour.cost = curr_tour->cost;
                best_tour.count = curr_tour->count;
                best_tour.path = curr_tour->path;
            }
            omp_unset_lock(&lock);
            }
        else {
            int temp = curr_tour->path[curr_tour->count-1];
            Edge *ptr = edges_list[temp];
            while(ptr != NULL) {
                if(feasible(curr_tour, ptr)) {
                    push(my_stack, add_city(curr_tour, ptr));
                }
                ptr = ptr->next;
            }
        }
    }
    return 0;
}

int feasible(tour *curr_tour, Edge *next) {
    if ((curr_tour->cost + next->cost) >= best_tour.cost){
        return 0;
    }
    
    if(curr_tour->count == num_cities){
        if(next->city == 0){
            return 1;
        }
        //otherwise return false
        else return 0;
    }
    else{
        for(int i = 0; i < curr_tour->count; i++){
            if(curr_tour->path[i] == next->city)
                return 0;
        }
    }
    return 1;
}

tour *add_city(tour *curr_tour, Edge *next){
    tour *retval = malloc(sizeof(tour));
    retval->path = malloc(sizeof(int) * (num_cities + 1));
    retval->cost = curr_tour->cost + next->cost;
    retval->path = memcpy(retval->path, curr_tour->path,curr_tour->count * sizeof(int));
    retval->count = curr_tour->count + 1;
    retval->path[retval->count - 1] = next->city;
    return retval;
}

int tokenize_line(char *input) {
    char *delims = "( ,\r\n\0)";
    
    if (atoi(input) > 0) {
        num_cities = atoi(input);
        if ( num_cities > 0) {
            edges_list = ( Edge **)malloc(sizeof( Edge*) * num_cities );
            for (int i = 0; i < num_cities; ++i) {
                edges_list[i] = NULL;
            }
        }
        return 1;
    }
    else {
        int city_origin = atoi(strtok(input,delims));
        int city_dest = atoi(strtok(NULL, delims));
        int cost = atoi(strtok(NULL, delims));
        printf("%d %d %d\n", city_origin, city_dest, cost);
         Edge *temp = ( Edge *)malloc(sizeof( Edge));
        temp->city = city_dest;
        temp->cost = cost;
        temp->next = edges_list[city_origin];
        edges_list[city_origin] = temp;
        }
    return 0;
}
