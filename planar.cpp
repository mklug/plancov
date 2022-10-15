// To compile:
// c++ -std=c++11 -I ~/coding/c++/boost/boost_1_80_0 planar.cpp -o planar

#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <iostream>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>

#ifdef __cplusplus
extern "C"
{
#endif
#include "graph_label.c"
#ifdef __cplusplus
}
#endif
struct VD { };
struct ED { };

// VD and ED are just trivial structs
using Graph  = boost::adjacency_matrix<boost::directedS, VD, ED>;
using Vertex = Graph::vertex_descriptor;
using Edge   = Graph::edge_descriptor;

int main() {

	srand(time(NULL));
	graph* G = graphInitialize((char*)"graphs/negami/D_2");
	//graph* G = graphInitialize((char*)"graphs/k3_3");
	//graph* G = graphInitialize((char*)"graphs/k4");	
	//graph* G = graphInitialize((char*)"graphs/petersen");
	//graph* G = graphInitialize((char*)"graphs/negami/k_2_2_2_1");
	

// Check below -- do we need to worry about freeing h??	

	int trials = 100;
	for (int k = 0; k < trials; k++)
	{

		int d = rand() % 100; //degree of the cover.     Can handle around 5000.
		if ((d % 2 != 0) || (d == 0) || (d == 1)) continue;
		int trials_with_d = 5000; //Number of covers we look at with degree d. 

		int planar = 0;
		int not_planar = 0;

		for (int i = 0; i<trials_with_d; i++)
		{
			edge_labeled_graph* G_lab = randomLabeling(G, d);	
			graph* H = constructCover(G_lab);
			//printGraph(H);

			const unsigned kNodesCount = H->V;
			Graph h { kNodesCount };
				for (int i = 0; i<H->V; i++)
			{
				for (int j = 0; j<i; j++)
				{
					if (H->adjacency_matrix[i][j] == 1)
					{       
						//std::cout << "Found edge " << i << "  " << j << "\n";
						add_edge(i,j,h);
						add_edge(j,i,h);
					}
				}
		}

		graphDestroy(H);
		labeledEdgeGraphDestroy(G_lab);

		//print_graph(g);
		//std::cout << "Your graph is planar? (1 means yes) " << boost::boyer_myrvold_planarity_test(h) << '\n';

		if (boost::boyer_myrvold_planarity_test(h)) planar++;
		else not_planar++;
		}

		std::cout << "The degree used was " << d << "\n";
		std::cout << "Out of the " << trials_with_d << " trials, we saw " << planar << " planar graphs and " 
			<< not_planar << " not planar graphs.\n";

	}
}

