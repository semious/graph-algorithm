#ifndef GRAPH_ALGORITHM_GRAPH_H
#define GRAPH_ALGORITHM_GRAPH_H

struct Node
{
  float x; // x coordinate
  float y; // y coordinate
};

struct Edge
{
  int sourceNodeArrayIdx; // node array index
  int targetNodeArrayIdx; // node array index
};

struct Point
{
  float x;
  float y;
} ;

struct Center
{
  float x;
  float y;
};

struct Cluster
{
  int *nodeArrayIdx;
  int nodeSize;
  float cx;
  float cy;
  int count;
};

#endif //GRAPH_ALGORITHM_GRAPH_H
