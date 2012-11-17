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

int tour_finder(void);
int feasible(tour curr_tour, int city);
int tokenize_line(char *input);
static int num_cities = 0;
struct Edge **edges_list;

int main(int argc, char * argv[]) {
    tour best_tour;
    char line[64];
    file = fopen( argv[1], "rt");
    
    while(fgets(line, 64, file) != NULL) {
        sscanf(line, "%s", &line);
        tokenize_line(line);
    }
        for (int i = 0; i < num_cities; ++i){
            for (int j = 0; j < 3; ++j){
                printf("%d %d %d asd\n", i, (&edges_list[i][j])->city, ((&edges_list[i][j])->next)->city);
            }
        }
    fclose(file);
    //after list is built
    #pragma omp parallel num_threads(4)
    {
    tour_finder();
    }
    
    return 0;
}

int tour_finder(void) {
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    struct Stack *my_stack = createStack();
    tour *curr_tour = (tour*)malloc(sizeof(tour));
    curr_tour->cost = 0;
    curr_tour->count = 1;
    curr_tour->path = NULL;
    
    //print debugging stuff
    push(my_stack, (void *)my_rank);
    int d = (int*)popBusyWait(my_stack);
    printf("%d\n", d);
    /*    
    push(my_stack, 0);
    
    while(!empty(my_stack)) {
        cur_tour = pop(my_stack);
        if(city_count(curr_tour) == n) {
            if(best_tour(curr_tour)) update_best_tour(curr_tour);
        }
        else {
            for(city = n-1; city >= 1; city--){
                if(feasible(curr_tour, city)){
                    add_city(curr_tour, city);
                    push(my_stack, curr_tour);
                    remove_last_city(curr_tour);
                }
            }
        free_tour(curr_tour);
        }
    }*/
    
    return 0;
}

int feasible(tour curr_tour, int city) {
    return 0;
}
int tokenize_line(char *input) {
    char *delims = "( ,\r\n)";
    
    if (atoi(input) > 0) {
        num_cities = atoi(input);
        if ( num_cities > 0) {
            edges_list = (struct Edge **)malloc(sizeof(struct Edge*) * num_cities );
            for (int i = 0; i < num_cities; ++i) {
                //edges_list[i]->next = NULL;
            }
        }
        return 1;
    }
    else {
        int city_origin = atoi(strtok(input,delims));
        int city_dest = atoi(strtok(NULL, delims));
        int cost = atoi(strtok(NULL, delims));
        struct Edge *temp = (struct Edge *)malloc(sizeof(struct Edge));
        temp->city = city_dest;
        temp->cost = cost;
        temp->next = edges_list[city_origin];
        edges_list[city_origin] = temp;
        }
    return 0;
}
