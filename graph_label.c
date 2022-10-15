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
	graph graph;
	labeled_oriented_edge* labeled_oriented_edges; // Issue - this makes it hard to search
} edge_labeled_graph;


// Given an oriented edge labeled graph and i ,j returns the perm on the edge (or null if there is none).
Perm permOnEdge(edge_labeled_graph* G_lab, int i, int j)
{
	int E = G_lab->graph.E;
	labeled_oriented_edge* edges  = G_lab->labeled_oriented_edges;
	Perm P = NULL;
	for (int l = 0; l < E; l++)
		if ((edges[l].start == i) && (edges[l].end == j))
			P = edges[l].label;
	return P;
}

graph* graphInitialize(char* fileName)
{
	graph* G = (graph*)malloc(sizeof(graph));
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) printf("Error when opening the file."); 
	int V, E; 
	fscanf(fp, "%d %d[^\n]",&V, &E);

	G->V = V;
	G->E = E;
	G->adjacency_matrix = readAdjacencyMatrix(fileName);
	return G;
}

void graphDestroy(graph* G)
{
	destroyArray(G->adjacency_matrix);
	free(G);
}

void labeledEdgeGraphDestroy(edge_labeled_graph* G_lab)
{
	//graphDestroy(&G_lab->graph);
	free(G_lab->labeled_oriented_edges); // Is this freeing everything?
	free(G_lab);
}

void printGraph(graph* G)
{printArray(G->adjacency_matrix, G->V, G->V);}

void printEdgeLabeledGraph(edge_labeled_graph* G_lab)
{
	printf("The adjacency matrix is given by:\n");
	printGraph( &(G_lab->graph));
	int E = G_lab->graph.E;
	printf("The permutation labeling is given by:\n");
	for (int i = 0; i < E; i++)
	{
		printf("%d %d : ",G_lab->labeled_oriented_edges[i].start, G_lab->labeled_oriented_edges[i].end);
		print_perm(G_lab->labeled_oriented_edges[i].label);
	}
}


bool isConnected(graph* G)
{return isConnectedMatrix(G->adjacency_matrix, G->V);}

//Gives a random labeling by permutations on k letters to the edges of G.
edge_labeled_graph* randomLabeling(graph* G, int k)
{
	edge_labeled_graph* G_lab = (edge_labeled_graph*)malloc(sizeof(edge_labeled_graph));
	G_lab->graph = *G; //Copies the graph... Maybe bad.
	G_lab->labeled_oriented_edges = (labeled_oriented_edge*)malloc(G->E*sizeof(labeled_oriented_edge));

	int l = 0;
	for (int i = 0; i < G->V; i++)
		for (int j = 0; j<i; j++)
			if (G->adjacency_matrix[i][j] == 1)
			{
				G_lab->labeled_oriented_edges[l].start = i;
				G_lab->labeled_oriented_edges[l].end = j;
				G_lab->labeled_oriented_edges[l].label = random_perm(k);
				l++;
			}
	return G_lab;
}

//UNTESTED
graph* constructCover(edge_labeled_graph* G)
{
	graph* G_cov = (graph*)malloc(sizeof(graph));
	int k = (G->labeled_oriented_edges[0].label)->parent_group; // The degree of the cover.  
	G_cov->V = G->graph.V * k;
	G_cov->E = G->graph.E * k;
	G_cov->adjacency_matrix = createArray(G_cov->V, G_cov->V);

	for (int i = 0; i < G->graph.V; i++)
		for (int j = 0; j < i; j++)
			if (G->graph.adjacency_matrix[i][j] == 1)
			{
				Perm P = permOnEdge(G,i,j); 
				for (int l = 1; l <= k; l++)
				{
					int a =  i*k + (l-1);
					int b =  j*k + (perm_action(P, l) - 1);
					G_cov->adjacency_matrix[a][b] = G_cov->adjacency_matrix[b][a] = 1;
				}
			}
	return G_cov;
}
/*
int main()
{

	srand(time(NULL));
	//graph* G = graphInitialize("graphs/petersen");
	graph* G = graphInitialize("graphs/k3_3");
	printGraph(G);
	printf( isConnected(G) ? "It's connected!\n" : "It's not connected\n");
	printf( isConnected(graphInitialize("graphs/k3_3")) ? "It's connected!\n" : "It's not connected\n");

	edge_labeled_graph* G_lab = randomLabeling(G, 1);
	printf( isConnected(&(G_lab->graph)) ? "It's connected!\n" : "It's not connected\n");
	
	printGraph( &(G_lab->graph));
	printEdgeLabeledGraph(G_lab);

	graph* H = constructCover(G_lab);
	printGraph(H);

	for (int i = 0; i < H->V; i++)
	{
		for (int j = 0; j < i; j++)
			printf("%d", H->adjacency_matrix[i][j]);
	}

	int M = 100;
	int total_connected = 0;
	for (int i=0; i<M; i++)
	{
		edge_labeled_graph* G_lab = randomLabeling(G, 1);
		graph* H = constructCover(G_lab);
		if (isConnected(H)) total_connected++;
	}
	printf("%f\n", (float)(total_connected) / M );

	graphDestroy(G);
	graphDestroy(H);

	labeledEdgeGraphDestroy(G_lab);
}
*/

