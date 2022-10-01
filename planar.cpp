// To compile:
// c++ -std=c++11 -I ~/coding/c++/boost/boost_1_80_0 boost_graph_test.cpp -o example
#include <boost/graph/boyer_myrvold_planar_test.hpp>
//#include <boost/graph/adjacency_list.hpp>
#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif
#include "graph_dt.c"
#ifdef __cplusplus
}
#endif

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>
struct VD { };
struct ED { };

// VD and ED are just trivial structs
using Graph  = boost::adjacency_matrix<boost::directedS, VD, ED>;
using Vertex = Graph::vertex_descriptor;
using Edge   = Graph::edge_descriptor;

int main() {


	srand(time(NULL));
	graph* G = graphInitialize((char*)"graphs/k3_3");
	//printGraph(G);
	edge_labeled_graph* G_lab = randomLabeling(G, 2);	
	graph* H = constructCover(G_lab);
	printGraph(H);

	//printArray(H->adjacency_matrix, H->V, H->V);


// It seems like H->adjacency_matrix is not what it is supposed to be!!


	//const unsigned kNodesCount = 4;
	//Graph g { H->V };
	const unsigned kNodesCount = H->V;
    	Graph g { kNodesCount };
	for (int i = 0; i<H->V; i++)
	{
		for (int j = 0; j<i; j++)
		{
			if (H->adjacency_matrix[i][j] == 1)
			{       
				//std::cout << "Found edge " << i << "  " << j << "\n";
				add_edge(i,j,g);
				add_edge(j,i,g);
			}
		}
	}
	print_graph(g);

	std::cout << "Your graph is planar? (1 means yes) " << boost::boyer_myrvold_planarity_test(g) << '\n';

}

