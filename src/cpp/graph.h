#ifndef GRAPH_ALGORITHM_GRAPH_H
#define GRAPH_ALGORITHM_GRAPH_H

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

struct Point
{
  float x;
  float y;
};

struct Center
{
  float x;
  float y;
};

struct Cluster
{
  size_t *nodeArrayIdx;
  size_t node_size;
  float cx;
  float cy;
};

#endif //GRAPH_ALGORITHM_GRAPH_H
