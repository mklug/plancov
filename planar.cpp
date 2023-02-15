// To compile:
// c++ -std=c++11 -I ~/coding/c++/boost/boost_1_80_0 planar.cpp -o planar

#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <iostream>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>

#include "graph.h"
#include "perms.h"
#include "graph_label.h"

struct VD { };
struct ED { };

using Graph  = boost::adjacency_matrix<boost::directedS, VD, ED>;
using Vertex = Graph::vertex_descriptor;
using Edge   = Graph::edge_descriptor;

int main(int argc, char *argv[]) 
{

	char* graphFilePath;
	int numberTrials; // Total number of different degres that are randomly picked
	int maxDegree; // Maximum degree to consider.
	int trialsFixedDegree; // Number of random covers examined for a fixed degree. 

	if (argc == 1) // Use default values.
	{
		graphFilePath = (char*)"graphs/k_2_2_2_1";
		numberTrials = 100;
		maxDegree = 500; // Can handle around 5000 on my machine.
		trialsFixedDegree = 100;
	} else 
	{
		graphFilePath = argv[1];
		numberTrials = atoi(argv[2]);
		maxDegree = atoi(argv[3]);
		trialsFixedDegree = atoi(argv[4]); 
	}

	srand(time(NULL));
	graph* G = graphInitialize(graphFilePath);
	
	for (int k = 0; k < numberTrials; k++)
	{

		int d = rand() % maxDegree;
		// There will not be any odd planar covers (see Archdeacon and Richter).  
		if ((d % 2 != 0) || (d == 0) || (d == 1)) continue;

		int planar = 0;
		int not_planar = 0;

		for (int i = 0; i<trialsFixedDegree; i++)
		{
			edge_labeled_graph* G_lab = randomLabeling(G, d);	
			graph* H = constructCover(G_lab);

			const unsigned kNodesCount = H->V;
			Graph h { kNodesCount };
			for (int i = 0; i<H->V; i++)
			{
				for (int j = 0; j<i; j++)
				{
					if (H->adjacency_matrix[i][j] == 1)
					{       
						add_edge(i,j,h);
						add_edge(j,i,h);
					}
				}
			}

			graphDestroy(H);
			labeledEdgeGraphDestroy(G_lab);

			if (boost::boyer_myrvold_planarity_test(h)) planar++;
			else not_planar++;
		}

		std::cout << "The degree used was " << d << "\n";
		std::cout << "Out of the " << trialsFixedDegree << " trials, we saw " << planar << " planar graphs and " 
			<< not_planar << " not planar graphs.\n";
	}
}

