#ifndef GRAPH_ALGORITHM_GRAPH_HPP
#define GRAPH_ALGORITHM_GRAPH_HPP

struct Node
{
  float x; // x coordinate
  float y; // y coordinate
};

struct Edge
{
  size_t src_node_idx; // node array index
  size_t target_node_idx; // node array index
};

struct Center
{
  float x;
  float y;
};

struct Cluster
{
  size_t *node_array_idx;
  size_t node_size;
  float cx;
  float cy;
};

#endif //GRAPH_ALGORITHM_GRAPH_HPP
