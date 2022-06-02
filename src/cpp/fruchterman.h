#ifndef Fruchterman_H
#define Fruchterman_H

#include "graph.h"

void calRepulsive(const Node *nodes, size_t nodeSize, Point *displacements, float k2);

void calAttractive(const Node *nodes, size_t nodeSize, const Edge *edges, size_t edgeSize, Point *displacements, float k);

void calCluster(const Node *nodes, size_t nodeSize, const Cluster *clusters, size_t clusterSize, Point *displacements, float clusterGravity, float k);

void calGravity(Node *nodes, size_t nodeSize, Point *displacements, float gravity, float k, Center *center);

// void reCalNodesPosition(Node *nodes, size_t nodeSize, Point *displacements, unsigned int clusterSize, float speed);
#endif
