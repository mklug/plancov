#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "list.h"

int** createArray(int m, int n) // Creates an m-by-n array.  Returns is filled with 0s.
{
    int* values = calloc(m*n, sizeof(int));
    int** rows = malloc(m*sizeof(int*));
    for (int i=0; i<m; ++i) rows[i] = values + i*n;
    return rows;
}

void destroyArray(int** arr) // Frees memory allocated to an array.
{
    free(*arr);
    free(arr);
}

int** readAdjacencyMatrix(char* fileName) // Reads adjacency matrix from a file.  First line is numbers "V E".
					  // Other lines are the edges (e.g., 2 3 or 0 1).
					  // Must have line end on the last edge line also.
{
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) printf("Error when opening the file."); 

	int V, E; 
	fscanf(fp, "%d %d[^\n]",&V, &E);
	int** arr = createArray(V, V);
	int x, y; 

	for (int i=0; i<V; i++) arr[i][i] = 0;  // Make the diagonal all 0.
	for (int j=0; j<E; j++)
	{
		fscanf(fp, "%d %d[^\n]", &x, &y);
		arr[x][y] = arr[y][x] = 1;
	}	
	fclose(fp);
	return arr;
}

int** randAdjacencyMatrix(int V) // Returns a random adjacency matrix wiht each edge with probability 0.5.
{
	srand(time(NULL));
	int** arr = createArray(V, V);
	for (int i=0; i<V; i++) arr[i][i] = 0; 
	for (int i=0; i<V; i++)
		for (int j=0; j<i; j++) arr[i][j] = arr[j][i] = rand() % 2;
	return arr;
}

void printArray(int** arr, int m, int n) // Prints an array.
{
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++) printf("%d ", arr[i][j]);
		printf("\n");
	}	
}

typedef struct adjacencyList // Adjacency list representation of graphs.
{ 
int size;
link* array; 
} adjacencyList;

adjacencyList* createAdjacencyList(int V)
{
	adjacencyList* G = malloc(sizeof(adjacencyList));
	G->size = V;
	G->array = malloc(V*sizeof(link*));
	for (int i=0; i<V; i++) G->array[i] = NULL;
	return G;
}

void destroyAdjacencyList(adjacencyList* G)
{
	for (int i = 0; i<G->size; i++)
	{
		link x = G->array[i];
		while (x != NULL)
		{
			link t = x->next;
			free(x);
			x = t;
		}
	}
	free(G);
}

void printAdjacencyList(adjacencyList* G)
{
	int V = G->size;
	for (int i=0; i<V; i++)
	{
		printf("%d: ",i);
		link x = G->array[i];
		if (x==NULL) ;
		else
		{
			printf("%d ", x->item);
			while (x->next!=NULL)
			{
				x = x->next;
				printf("%d ", x->item);
			}
		}
		printf("\n");
	}
}

bool isEdge(adjacencyList* G, int a, int b)
{
	link x = G->array[a];
	if (x==NULL) return false;

	while ((x->next)!=NULL)
	{
		if (x->item==b) return true;
		x = x->next;
	}
	return false;
}

void addVertxAdjacencyList(adjacencyList* G, int a, int b) // For vertices a and b in an adjacency list, add the edge ab.
{
	if ((a==b) || isEdge(G,a,b)) return;
	link al = G->array[a];
	link bl = G->array[b];
	link new_a = init_link(a);
	link new_b = init_link(b);
	if (al == NULL) G->array[a] = new_b;
	else
	{
		while (al->next!=NULL) al = al->next;
		al->next = new_b;
	}

	if (bl == NULL) G->array[b] = new_a;
	else
	{
		while (bl->next!=NULL) bl = bl->next;
		bl->next = new_a;
	}
}

adjacencyList* matrixToList(int** arr, int V)
{
	adjacencyList* G = createAdjacencyList(V);
	for (int i=0; i<V; i++)
	{
		for (int j=0; j<i; j++)
		{
			if (arr[i][j]==1) addVertxAdjacencyList(G,i,j);
		}
	}
	return G;
}

// Connectivity algorithm (a recursive implementaion of depth-first search.

void traverse(int k, adjacencyList* G, int* visited)
{
	link t;
	visited[k] = 1;
	int V = G->size;
	for (t = G->array[k]; t != NULL; t = t->next)
		if (!visited[t->item]) traverse(t->item, G, visited);
}

bool isConnectedList(adjacencyList* G)
{
	int* visited = calloc(G->size, sizeof(Item));
	if (visited==NULL)
	{
		printf("Error allocating memory in isConnectedList\n");
		return false;
	}
	traverse(0, G, visited);
	bool b = true;
	for (int i = 0; i < G->size; i++)
		if (visited[i] != 1)
		{
			b = false;
			break;
		}
	free(visited);
	return b;
}

bool isConnectedMatrix(int** arr, int V)
{return isConnectedList(matrixToList(arr,V));}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
int main()
{
	int** a = readAdjacencyMatrix("graphs/k4");
	printArray(a, 4, 4);

	int** b = readAdjacencyMatrix("graphs/k3_3");
	printArray(b, 6, 6);

	int** c = readAdjacencyMatrix("graphs/k5");
	printArray(c, 5, 5);

	int** p = readAdjacencyMatrix("graphs/petersen");
	printArray(p, 10, 10);
	printAdjacencyList(matrixToList(p,10));

	printf("\n\n\n");
	printArray(randAdjacencyMatrix(30),30,30);
	
	int** d = randAdjacencyMatrix(20);
	adjacencyList* H = matrixToList(d,20);
	printAdjacencyList(H);
	printArray(d,20,20);

	printf("The graph is connected? ");

	int n = 1000; //Currently waiting on 10000
	int** mat = randAdjacencyMatrix(n);
	printf( isConnectedMatrix(mat, n) ? "true\n" : "false\n" );
	//printArray(mat, n, n);

}
*/

