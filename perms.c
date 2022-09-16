#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

struct perm 
{
	int parent_group;
	int* array;
};

typedef struct perm perm;
typedef struct perm* Perm;

perm* perm_initialize(int *array, int n) // Initializes a permutation given by the array in S_n.
{
	perm* g = malloc(sizeof(perm));
	g->parent_group = n;
	g->array = malloc(n*sizeof(int));
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







/*
bool array_eq(int *x, int *y, int n) //Auxillary function - given two length n arrays, returns if they are equal.  
{
	for (int i = 0; i<n; i++) {if (x[i] != y[i]) return false;}
	return true;
}
*/

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

Linked_list* perm_to_cyle(perm* g)
{
	int n = g->parent_group;
	Linked_list* L = malloc(n*sizeof(Linked_list)); // Storing the cylces.  
	int visited[n], all_ones[n];
	for (int i = 0; i < n; i++) 
	{	
		visited[i] = 0;
		all_ones[i] = 1; //Keeps track of the visited numbers and compares.  
	}

	int cycle_number = 0;
	while (!(array_compare(visited, all_ones, n) == -1))
	{
		//L[cycle_number] = init_linked_list();
	
	}
	
	

	return L;	
}

/*
void print_cycle_decomposition(perm* g)
{

}
*/






int main() 
{

	int g_array[] = {1,3,2};
	Perm g = perm_initialize(g_array, 3);
	print_perm(g);
	
	
	int h_array[] = {1,2,3};
	Perm h = perm_initialize(h_array, 3);
	print_perm(h);


	Perm gh = perm_mult(g,h);
	print_perm(gh);

	printf(perm_EQ(g,h) ? "true" : "false");	
	printf("\n");	
	printf(perm_EQ(g,gh) ? "true" : "false");	
	printf("\n");	
	printf(perm_EQ(h,gh) ? "true" : "false");	
	printf("\n");	

	int k_array[] = {1,3,2,5,6,4,7};
	Perm k = perm_initialize(k_array, 7);
	print_perm(k);
	print_perm(perm_inverse(k));
	print_perm(perm_mult(perm_inverse(k),k));

	print_perm(perm_inverse(perm_inverse(k)));

	print_perm(id_perm(10));

	printf(perm_EQ(perm_mult(k,perm_inverse(k)),id_perm(7)) ? "true" : "false");	
	printf("\n");

	printf("%d\n",perm_action(g,2));


	free_perm(g);
	free_perm(h);

	Linked_list l = init_linked_list(0);
	add_linked_list_end(l,1);
	add_linked_list_end(l,2);
	add_linked_list_end(l,3);
	print_linked_list(l);
	free_linked_list(l);


	int x[3] = {1,2,3};
	int y[3] = {1,2,4};
	int z[3] = {1,2,3};
	printf("%d\n", array_compare(x,y,3));
	printf("%d\n", array_compare(x,z,3));


// To do: random permutation.  


	return 0;
}
