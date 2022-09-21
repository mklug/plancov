#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int** createArray(int m, int n) // Creates an m-by-n array.  Returns is filled with 0s.
{
    int* values = calloc(m*n, sizeof(int));
    int** rows = malloc(m*sizeof(int*));
    for (int i=0; i<m; ++i)
    {
        rows[i] = values + i*n;
    }
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
	if (fp == NULL) 
	{
		printf("Error when opening the file."); 
	}

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
		for (int j=0; j<i; j++)
		{
			arr[i][j] = arr[j][i] = rand() % 2;
		
		}
	return arr;
}

void printArray(int** arr, int m, int n) // Prints an array.
{
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}	
}

// To do: adjacency list graph implementation.  
// Recursive implementation of depth-first search connectivity algorithm.
//bool is_connected(int** arr, int V)
//{
//}

typedef int Item;
typedef struct node* link;
typedef struct node
{
Item item;
link next;
} node;

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
	for (int i=0; i<V; i++)
	{
		G->array[i] = NULL;
	}
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

// Note: this is redundant from the list.c file -- fix.  
link init_link(Item n) // Initializes a node pointing to NULL with label n. Returns pointer to the node.
{
	link x;
	x = malloc(sizeof(node));
	x->next = NULL;
	x->item = n;
	return x;
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

int main()
{
	/*
	int** arr = createArray(2,2);
	arr[0][0] = 1;
	arr[0][1] = 2;
	arr[1][0] = 3;
	arr[1][1] = 4;
	
	printArray(arr, 2, 2);
	destroyArray(arr);
	*/
	// Just the file name call i want is not working.
	//int** b = readAdjacencyMatrix("/graphs/k3_3");
	/*
	int** a = readAdjacencyMatrix("graphs/k4");
	printArray(a, 4, 4);

	int** b = readAdjacencyMatrix("graphs/k3_3");
	printArray(b, 6, 6);

	int** c = readAdjacencyMatrix("graphs/k5");
	printArray(c, 5, 5);

	int** p = readAdjacencyMatrix("graphs/petersen");
	printArray(p, 10, 10);

	printf("\n\n\n");
	printArray(randAdjacencyMatrix(30),30,30);
	*/

	int** d = randAdjacencyMatrix(20);
	adjacencyList* H = matrixToList(d,20);
	printAdjacencyList(H);
	printArray(d,20,20);

	adjacencyList* G = createAdjacencyList(4);
	//printf(al==NULL?"true\n":"false\n");
	//al = new_b;

	addVertxAdjacencyList(G, 0, 1);
	addVertxAdjacencyList(G, 0, 2);
	addVertxAdjacencyList(G, 0, 3);
	addVertxAdjacencyList(G, 1, 3);
	addVertxAdjacencyList(G, 1, 0);



	printf(isEdge(G,0,1)?"true\n":"false\n");
	printf(isEdge(G,0,2)?"true\n":"false\n"); // Loops forever. 
	printf(isEdge(G,1,3)?"true\n":"false\n"); 
	printf(isEdge(G,2,3)?"true\n":"false\n"); 


	printf(G->array[0]==NULL?"true\n":"false\n"); 
	//printf("%d\n", (G->array[0])->item);

	printAdjacencyList(G);
	//destroyAdjacencyList(G);
}
