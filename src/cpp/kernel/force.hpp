#ifndef Fruchterman_H
#define Fruchterman_H

#include "src/cpp/graph.hpp"

namespace graph_algo
{
  void calculate_repulsive_force(Node *nodes, size_t node_size, Node *out, float k);

  void calculate_attractive_force(const Node *nodes, const Edge *edges, size_t edge_size, Node *out, float k);

  void calculate_cluster_force(const Node *nodes, const Cluster *clusters, size_t cluster_size, Node *out, float cluster_gravity, float k);

  void calculate_gravity_force(Node *nodes, size_t node_size, Node *out, float gravity, float k, Center *center);

// void reCalNodesPosition(Node *nodes, size_t nodeSize, Point *displacements, unsigned int clusterSize, float speed);
}
#endif
