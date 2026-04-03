#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int citiesAmount, waysAmount;
    fscanf(file, "%d %d", &citiesAmount, &waysAmount);
    int** graph = (int**)malloc(citiesAmount * sizeof(int*));
    for (int i = 0; i < citiesAmount; i++) {
        graph[i] = (int*)malloc(citiesAmount * sizeof(int));
        for (int j = 0; j < citiesAmount; j++) {
            graph[i][j] = -1;
        }
    }

    for (int i = 0; i < waysAmount; i++) {
        int city1, city2, cost;
        fscanf(file, "%d %d %d", &city1, &city2, &cost);
        graph[city1][city2] = cost;
        graph[city2][city1] = cost;
    }

    
    int* ownersOfCities = (int*)malloc(citiesAmount * sizeof(int));
    for (int i = 0; i < citiesAmount; i++) {
        ownersOfCities[i] = -1;
    }

    int capitalAmount;
    fscanf(file, "%d", &capitalAmount);
    int* capitalCities = (int*)malloc(capitalAmount * sizeof(int));
    for (int i = 0; i < capitalAmount; i++) {
        fscanf(file, "%d", &capitalCities[i]);
        ownersOfCities[capitalCities[i]] = capitalCities[i];
    }


    PriorityQueue* pq = createPriorityQueue();
    // enqueue(pq, 3);
    // enqueue(pq, 2);
    // enqueue(pq, 15);
    // enqueue(pq, 5);
    // enqueue(pq, 4);
    // enqueue(pq, 45);


    freePriorityQueue(pq);
    

    fclose(file);
 
    return 0;
}