#include <iostream>
#include <cmath>
#include <ctime>
#include <wasm_simd128.h>
#include "graph.h"

struct VectorDis
{
  float x[4];
  float y[4];
};


namespace graph_algo
{
  void calculate_repulsive_force_simd(v128_t vx_mm, v128_t vy_mm, v128_t sign, float k2, VectorDis *ret);

  void calRepulsive2(const Node *nodes, size_t nodeSize, Node *displacements, float k2);

  void calculate_repulsive_force(const Node *nodes, const size_t node_size, Node *out, const float k);


  void calculate_attractive(const Node *nodes, const size_t node_size, const Edge *edges, const size_t edge_size, Node *out, const float k);

  void calculate_cluster(const Node *nodes, const size_t node_size, const Cluster *clusters, const size_t cluster_size, Node *displacements, const float cluster_gravity, const float k);

  void calculate_gravity(Node *nodes, size_t node_size, Node *out, float gravity, float k, Center *center);

}



