#ifndef GRAPH_LABEL_H
#define GRAPH_LABEL_H

#include "graph_label.c"

graph* graphInitialize(char* fileName);
void graphDestroy(graph* G);
void labeledEdgeGraphDestroy(edge_labeled_graph* G_lab);
void printGraph(graph* G);
void printEdgeLabeledGraph(edge_labeled_graph* G_lab);
bool isConnected(graph* G);
edge_labeled_graph* randomLabeling(graph* G, int k);
graph* constructCover(edge_labeled_graph* G);

#endif
