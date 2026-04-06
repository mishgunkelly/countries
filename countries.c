#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#define UNOWNED -1
#define INVALID_COST -1

int God(char *inputFilePath, char *outputFilePath)
{

    FILE *inputFile = fopen(inputFilePath, "r");

    if (inputFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    int citiesAmount, waysAmount;
    fscanf(inputFile, "%d %d", &citiesAmount, &waysAmount);
    int** graph = (int**)malloc(citiesAmount * sizeof(int*));
    for (int i = 0; i < citiesAmount; i++) {
        graph[i] = (int*)malloc(citiesAmount * sizeof(int));
        for (int j = 0; j < citiesAmount; j++) {
            graph[i][j] = INVALID_COST;
        }
    }

    for (int i = 0; i < waysAmount; i++) {
        int city1, city2, cost;
        fscanf(inputFile, "%d %d %d", &city1, &city2, &cost);
        graph[city1 - 1][city2 - 1] = cost;   //
        graph[city2 - 1][city1 - 1] = cost;   //
    }

    
    int* ownersOfCities = (int*)malloc(citiesAmount * sizeof(int));
    for (int i = 0; i < citiesAmount; i++) {
        ownersOfCities[i] = UNOWNED;
    }



    PriorityQueue* pq = createPriorityQueue();

    int capitalAmount;
    fscanf(inputFile, "%d", &capitalAmount);
    int* capitalCities = (int*)malloc(capitalAmount * sizeof(int));
    for (int i = 0; i < capitalAmount; i++) {
        fscanf(inputFile, "%d", &capitalCities[i]);
        capitalCities[i]--;  //
        ownersOfCities[capitalCities[i]] = capitalCities[i];
        for (int j = 0; j < citiesAmount; j++) {
            if (graph[capitalCities[i]][j] != INVALID_COST) {
                Edge edge = {j, graph[capitalCities[i]][j], capitalCities[i]};
                enqueue(pq, edge);
            }
        }
    }

    while (!isEmpty(pq))
    {
        Edge edge = dequeue(pq);
        if (ownersOfCities[edge.city] == UNOWNED) {
            ownersOfCities[edge.city] = edge.owner;
            for (int j = 0; j < citiesAmount; j++) {
                if (graph[edge.city][j] != INVALID_COST && ownersOfCities[j] == UNOWNED) {
                    Edge newEdge = {j, graph[edge.city][j], edge.owner};
                    enqueue(pq, newEdge);
                }
            }
        }
    }
    
    FILE *outputFile = fopen(outputFilePath, "w");
    for (int i = 0; i < capitalAmount; i++) {
        fprintf(outputFile, "%d: ", capitalCities[i] + 1);  //
        for (int j = 0; j < citiesAmount; j++) {
            if (ownersOfCities[j] == capitalCities[i]) {
                fprintf(outputFile, "%d ", j + 1);  //
            }
        }
        fprintf(outputFile, "\n");
    }

    freePriorityQueue(pq);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}