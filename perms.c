#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "list.h"


struct perm 
{
	int parent_group;
	int* array;
};

perm* perm_initialize(int *array, int n) // Initializes a permutation given by the array in S_n.
{
	perm* g = (perm*)malloc(sizeof(perm));
	g->parent_group = n;
	g->array = (int*)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++) (g->array)[i] = array[i];
	return g;
}

perm* perm_mult(perm* g, perm* h) // Multiplies two permustions.
{
	int n = g->parent_group;
	if (n != h->parent_group) printf("You are trying to multiply elements in different groups.\n");
	int array[n];
	for (int i = 0; i < n; i++) array[i] = (g->array)[(h->array)[i]-1];
	perm* gh = perm_initialize(array, n);	
	return gh;
}

bool perm_EQ(perm* g, perm* h) // Determines if two permutations are equal.
{
	bool x = true;
	int n = g->parent_group;
	if (n == h->parent_group)
	{
		int i = 0;
	        while (i < n)
	 	{
			if (g->array[i] != h->array[i]) 
			{
				x = false;
				break;
			}
			i++;
		}		
	}
	else x = false;
	return x;
}

perm* perm_inverse(perm* g) // Inverts a permutation.
{
	int n = g->parent_group;
	int array[n];
	for (int i = 0; i < n; i++) array[g->array[i] - 1] = i + 1;
	perm* g_inverse = perm_initialize(array, n);
	return g_inverse;
}

perm* id_perm(int n) // Initializes the identity permutation in S_n.
{
	int id_array[n];
	for (int i = 0; i < n; i++) id_array[i] = i + 1;
	return perm_initialize(id_array, n);
}

int perm_action(perm* g, int k) // Returns g(k).
{
	if (k > g->parent_group) printf("Action is out of bounds.");
	return g->array[k-1];
}

void print_perm(perm* g) // Prints a permutation.  
{
	int n = g->parent_group;	
	printf("[ ");
	for (int i = 0; i < n; i++) printf("%d ", (g->array)[i]);
	printf("]\n");
}

void free_perm(perm* g) // Frees memory allocated to g.  
{	
	free(g->array);
	free(g);
}

int array_compare(int* x, int* y, int n) // Returns first nonequal location in two length n int arrays and -1 if equal.
{
	int i = 0;
	while (i < n)
	{
		if (x[i] != y[i]) return i;
		i++;
	}
	return -1;
}

Linked_list* perm_to_cycle(perm* g) //Builds an array of cicular linked lists describing the cycle decomposition of g.  
{
	int n = g->parent_group;
	Linked_list* L = (Linked_list*)malloc(n*sizeof(Linked_list)); // Storing the cylces.  
	for (int i = 0; i < n; i++) L[i] = NULL;
	int visited[n], all_ones[n];
	for (int i = 0; i < n; i++) 
	{	
		visited[i] = 0;
		all_ones[i] = 1; //Keeps track of the visited numbers and compares.  
	}

	int i;
	int cycle_number = 0;
	while (! ( array_compare(visited, all_ones, n) == -1) )   
	{							  
		i = array_compare(visited, all_ones, n);
		visited[i] = 1;
		L[cycle_number] = init_linked_list(i + 1); 	

		int j;
		while (visited[j = perm_action(g, i + 1) - 1] == 0)  
		{						    
			add_linked_list_end(L[cycle_number], j + 1); 
			visited[j] = 1;
			i = j;			
		}
		cycle_number++;		
	}
	return L;
}

void free_linked_list_array(Linked_list* L, perm* g) // Auxillary function used to free the linked list array created in perm_to_cycle.  
{
	int n = g->parent_group;
	for (int i = 0; i < n; i++)
	{
		free_linked_list(L[i]);
	}
	free(L);
}


// Need to add the freeing call....
void print_cycle_decomposition(perm* g)
{
	printf("The cycle decomposition is:\n");
	Linked_list* L;
	L = perm_to_cycle(g);
	int n = g->parent_group;
	for (int i = 0; i < n; i++)
	{
		if (L[i] != NULL) 
		{
			print_linked_list(L[i]);
		}	
	//free_linked_list_array(L, g);	
	}
}

// Auxillary function -- interchanges two values.   
void swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// Produces a random permutation on n letters. 
// WARNING - if you call multiple times a second, it will be the same.
perm* random_perm (int n)
{
	//srand(time(NULL)); Need to call this inside of main.
	int array[n];
	for (int i=0; i<n; i++) array[i] = i+1;
	perm* g = perm_initialize(array, n);

	for (int i = n-1; i > 0; i--)
	{
		int j = rand() % (i+1);
		swap(&g->array[i], &g->array[j]);
    	}
	return g;
}

