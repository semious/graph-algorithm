
#ifndef GRAPH_ALGORITHM_TEST_UTIL_H
#define GRAPH_ALGORITHM_TEST_UTIL_H

#include "graph.h"
#include <ctime>
void createRandNodes(Node *nodes, size_t count, short width, short height)
{
  srand(time(nullptr));
  for (size_t i = 0; i < count; i++)
  {
    nodes[i].x = rand() % width;
    nodes[i].y = rand() % height;
  }
}

void createRandEdges(Edge *edges, size_t count, size_t nodeSize)
{
  srand(time(nullptr));
  for (size_t i = 0; i < count; i++)
  {
    edges[i].sourceNodeArrayIdx = rand() % nodeSize;
    edges[i].targetNodeArrayIdx = rand() % nodeSize;
  }
}
#endif //GRAPH_ALGORITHM_TEST_UTIL_H
