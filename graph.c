#include <stdio.h>
#include <stdlib.h>

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

// Needs to be tested!!
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

void printArray(int** arr, int m, int n)
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
	


	int** b = readAdjacencyMatrix("graphs/k3_3");
	//FILE* q = fopen("perms.c", "r");
	//fclose(q);
	printArray(b, 6, 6);

}
