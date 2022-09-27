#include "graph.c"
#include "perms.c"

// Allows for flexibility with the implementation.  
typedef Perm Label;


typedef struct labeled_oriented_edge
{
	int start;
	int end;
	Label label;
} labeled_oriented_edge;

typedef struct graph
{ 
	int** adjacency_matrix;
	int V;
	int E;
} graph;

typedef struct edge_labeled_graph
{
	graph G;
	labeled_oriented_edge* labeled_oriented_edges;
} edge_labeled_graph;



//graph* graphInitialize(char* filename)
//{}

void graphDestroy(graph* G)
{}

//bool isConnected(graph G)
//{}


//graph* constructCover(edge_labeled_graph G)
//{}

// Make a spearate file with the planarity testing and whatnot.  



int main()
{}


