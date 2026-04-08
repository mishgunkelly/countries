#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#define UNOWNED -1
#define INVALID_COST -1

int God(const char *inputFilePath, const char *outputFilePath)
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



    int capitalAmount;
    fscanf(inputFile, "%d", &capitalAmount);
    PriorityQueue** pqs = (PriorityQueue**)malloc(capitalAmount * sizeof(PriorityQueue*));
    for (int i = 0; i < capitalAmount; i++) {
        pqs[i] = createPriorityQueue();
    }

    int* capitalCities = (int*)malloc(capitalAmount * sizeof(int));
    for (int i = 0; i < capitalAmount; i++) {
        fscanf(inputFile, "%d", &capitalCities[i]);
        capitalCities[i]--;  //
        ownersOfCities[capitalCities[i]] = capitalCities[i];
        for (int j = 0; j < citiesAmount; j++) {
            if (graph[capitalCities[i]][j] != INVALID_COST) {
                Edge edge = {j, graph[capitalCities[i]][j], capitalCities[i]};
                enqueue(pqs[i], edge);
            }
        }
    }




    bool* isPQEmpty = (bool*)malloc((sizeof(bool) * capitalAmount));
    for (int i = 0; i < capitalAmount; i++) {
        isPQEmpty[i] = false;
    }
    bool isEnd = false;
    while (!isEnd)
    {
        for (int i = 0; i < capitalAmount; i++) {
            if (isPQEmpty[i]) {
                continue;
            }
            Edge edge = dequeue(pqs[i]);
            while (!isEmpty(pqs[i]) && ownersOfCities[edge.city] != UNOWNED)
                edge = dequeue(pqs[i]);
            if (ownersOfCities[edge.city] == UNOWNED) {
                ownersOfCities[edge.city] = edge.owner;
                for (int j = 0; j < citiesAmount; j++) {
                    if (graph[edge.city][j] != INVALID_COST && ownersOfCities[j] == UNOWNED) {
                        Edge newEdge = {j, graph[edge.city][j], edge.owner};
                        enqueue(pqs[i], newEdge);
                    }
                }
            }
            if (isEmpty(pqs[i])) {
                isPQEmpty[i] = true;
            }
        }
        for (int i = 0; i < capitalAmount; i++) {
            if (!isPQEmpty[i]) {
                isEnd = false;
                break;
            }
            isEnd = true;
        }
    }
    
    FILE *outputFile = fopen(outputFilePath, "w");
    for (int i = 0; i < capitalAmount; i++) {
        fprintf(outputFile, "%d:", capitalCities[i] + 1);  //
        for (int j = 0; j < citiesAmount; j++) {
            if (ownersOfCities[j] == capitalCities[i]) {
                fprintf(outputFile, " %d", j + 1);  //
            }
        }
        fprintf(outputFile, "\n");
    }

    for (int i = 0; i < citiesAmount; i++) {
        free(graph[i]);
    }
    free(graph);
    for (int i = 0; i < capitalAmount; i++) {
        freePriorityQueue(pqs[i]);
    }
    free(pqs);
    free(capitalCities);
    free(ownersOfCities);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}