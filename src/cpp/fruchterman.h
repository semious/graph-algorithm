#ifndef Fruchterman_H
#define Fruchterman_H

#include "graph.h"

void calculate_repulsive_force(const Node *nodes, size_t nodeSize, Point *out, float k);

void calculate_attractive(const Node *nodes, size_t nodeSize, const Edge *edges, size_t edge_size, Point *out, float k);

void calculate_cluster(const Node *nodes, size_t nodeSize, const Cluster *clusters const size_t clusterSize, Point *displacements, float clusterGravity, const float k);

void calculate_gravity(Node *nodes, size_t nodeSize, Point *out, float gravity, float k, Center *center);

// void reCalNodesPosition(Node *nodes, size_t nodeSize, Point *displacements, unsigned int clusterSize, float speed);
#endif
