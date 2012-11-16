/*
 * Jordan Harmel
 * Vladimir Tsoy
 * Nov. 15, 2012
 *
 * CS 470 : Traveling Salesperson
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

FILE *file;

int main(int argc, char * argv[]) {
    char line[64];
    file = fopen( argv[1], "rt");
    
    while(fgets(line, 64, file) != NULL) {
        sscanf(line, "%s", &line);
        printf("%s", line);
    }
    fclose(file);
    return 0;
}