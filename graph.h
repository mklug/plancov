#ifndef GRAPH_H
#define GRAPH_H

#include "graph.c"

int** readAdjacencyMatrix(char* fileName);
int** randAdjacencyMatrix(int V);
adjacencyList* createAdjacencyList(int V);
void destroyAdjacencyList(adjacencyList* G);
void printAdjacencyList(adjacencyList* G);
bool isEdge(adjacencyList* G, int a, int b);
void addVertxAdjacencyList(adjacencyList* G, int a, int b);
adjacencyList* matrixToList(int** arr, int V);
bool isConnectedList(adjacencyList* G);

#endif
