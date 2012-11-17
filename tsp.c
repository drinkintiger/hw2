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
void partition_tree(int rank, struct Stack s);

int main(int argc, char * argv[]) {
    tour best_tour;
    char line[64];
    file = fopen( argv[1], "rt");
    
    while(fgets(line, 64, file) != NULL) {
        sscanf(line, "%s", &line);
        tokenize_line(line);
       printf("%s\n", line);
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
    char *temp = (char *)malloc(sizeof(input)+1);
    char *str_ptr = NULL;
    
    if (atoi(input) > 0) {
        num_cities = atoi(input);
        return 1;
    }
    else {
        for (int i = 0; i < strlen(input); ++i) {
            if ( '(' != input[i] && ')' != input[i] ){
                temp = strdup(&input[i]);
            }
        }
        printf("%s asdasdada \n", temp);
    }
    return 0;
}
