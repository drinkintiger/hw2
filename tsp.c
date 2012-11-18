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
int feasible(tour *curr_tour, struct Edge next, int city);
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
            for (int j = 0; (&edges_list[i][j])->next != NULL; ++j){
            //if ((&edges_list[i][j])->next != NULL){
                printf("Origin %d %d Destination: %d Cost: %d\n", i, j, (&edges_list[i][j])->city, (&edges_list[i][j])->cost);
            //}
            //else printf("City: %d Cost: %d\n",(&edges_list[i][j])->city, (&edges_list[i][j])->cost);
            }
        }
    fclose(file);
    //after list is built
    #pragma omp parallel num_threads(num_cities)
    {
    tour_finder();
    }
    
    return 0;
}

int tour_finder(void) {
    int my_rank = omp_get_thread_num();
    struct Stack *my_stack = createStack();
    tour *curr_tour = (tour*)malloc(sizeof(tour));
    curr_tour->cost = 0;
    curr_tour->count = 1;
    curr_tour->path = (int *)malloc(sizeof(int)*(num_cities+1));
    curr_tour->path[0] = 0;
    //print debugging stuff
    push(my_stack, (void *)curr_tour);
    tour *d = (int*)popBusyWait(my_stack);
    
    /*while(!empty(my_stack)) {
        curr_tour = pop(my_stack);
        if(curr_tour->count == num_cities) {
            if(best_tour(curr_tour)) update_best_tour(curr_tour);
        }
        else {
            for(city = num_cities-1; city >= 1; city--){
                if(feasible(curr_tour, Edge from city, int city)){
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

int feasible(tour *curr_tour, struct Edge next, int city) {
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
