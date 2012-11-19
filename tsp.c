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
void remove_last_city(tour *curr_tour);
static int num_cities = 0;
omp_lock_t lock;
struct Edge **edges_list;
tour best_tour;


int main(int argc, char * argv[]) {
    struct Stack *stack = createStack();
    omp_init_lock(&lock);
    char line[64];
    file = fopen( argv[1], "rt");
    (&best_tour)->cost = 2232323;
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
                t->count = 2;
                t->path= (int *)malloc(sizeof(int)*(num_cities+1));
                t->path[0] = i;
                t->path[1] = temp_list[i]->city;
                push(stack, (void *)t);
                temp_list[i] = temp_list[i]->next;
            }
        }
    fclose(file);
    
    #pragma omp parallel num_threads(num_cities)
    {
    tour_finder((tour *)popBusyWait(stack));
    }
    
    return 0;
}

int tour_finder(tour *curr_tour) {
    struct Stack *my_stack = createStack();
    push(my_stack, (void *)curr_tour);    

    while(!empty(my_stack)) {
        curr_tour = (tour *)popBusyWait(my_stack);
        if(curr_tour->count == num_cities) {
            omp_set_lock(&lock);
            if(curr_tour->cost < (&best_tour)->cost) {
                best_tour = *curr_tour;
            }
            omp_unset_lock(&lock);
        }
        else {
            for(int city = num_cities-1; city >= 1; city--){
                if(feasible(curr_tour, edges_list[curr_tour->path[curr_tour->count-1]], city)){
                    add_city(curr_tour, city);
                    push(my_stack, curr_tour);
                    remove_last_city(curr_tour);
                }
            }
        free(curr_tour);
        }
    }
    
    return 0;
}

int feasible(tour *curr_tour, struct Edge *next, int city) {
    struct Edge *temp = (struct Edge *)malloc(sizeof(struct Edge));
    temp = next;
    if(curr_tour->count == num_cities){
        while(temp->next!=NULL){
            if(temp->city==0){
                curr_tour->cost+=temp->cost;
                curr_tour->count+=1;
                curr_tour->path[curr_tour->count] = 0;
                return 1;
            }
            temp = temp->next;
        }
        //otherwise return false
        return 0;
    }
    else{
        for(int i = 0; i < curr_tour->count; i++){
            if(curr_tour->path[i]==city)
                return 0;
        }
        
        while(temp->next!=NULL){
            if(temp->city==city)
                return 1;
            temp = temp->next;
        }
    }
    
    return 1;
}

void add_city(tour *curr_tour, int city){
    struct Edge **temp_list = (struct Edge **)malloc(sizeof(struct Edge*) * num_cities );
    temp_list = edges_list;
    //Iterates through the edges_list looking for a match on the passed city, there will be a match sinice at this point it's feasible
    while(temp_list[curr_tour->path[curr_tour->count-1]]->city != city){
        temp_list[curr_tour->path[curr_tour->count-1]] = temp_list[curr_tour->path[curr_tour->count-1]]->next;
    }
    curr_tour->cost += temp_list[curr_tour->path[curr_tour->count-1]]->cost;
    curr_tour->path[curr_tour->count] = city;
    curr_tour->count += 1;
    free(temp_list);
}

void remove_last_city(tour *curr_tour){
    struct Edge **temp_list = (struct Edge **)malloc(sizeof(struct Edge*) * num_cities );
    curr_tour->count -= 1;
    //looks at the city before the added one, and looks for the city that was added
    while(temp_list[curr_tour->path[curr_tour->count-1]]->city!=curr_tour->count){
        temp_list[curr_tour->path[curr_tour->count-1]] = temp_list[curr_tour->path[curr_tour->count-1]]->next;
    }
    curr_tour->cost -= temp_list[curr_tour->path[curr_tour->count-1]]->cost;
    curr_tour->path[curr_tour->count] = -1;
    free(temp_list);
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
