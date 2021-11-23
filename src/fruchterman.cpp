#include <iostream>
#include <cmath>
#include <ctime>

#include "fruchterman.h"



void calRepulsive(const Node *nodes, const size_t nodeSize, Point *displacements, const float k2)
{
  for (size_t i = 0; i < nodeSize; i++)
  {
    for (size_t j = 0; j < nodeSize; j++)
    {
      if (i == j)
      {
        continue;
      }
      Node v = nodes[i];
      Node u = nodes[j];
      float vecX = v.x - u.x;
      float vecY = v.y - u.y;
      float vecLengthSqr = vecX * vecX + vecY * vecY;
      if (vecLengthSqr < 1e-6)
      {
        vecLengthSqr = 1.0;
        short sign = i > j ? 1 : -1;
        vecX = sign * 0.01;
        vecY = sign * 0.01;
      }
      float common = k2 / vecLengthSqr;
      displacements[i].x += vecX * common;
      displacements[i].y += vecY * common;
    }
  }
}

void calAttractive(const Node *nodes, const size_t nodeSize, const Edge *edges, const size_t edgeSize, Point *displacements, const float k)
{
  for (size_t i = 0; i < edgeSize; i++)
  {
    Edge edge = edges[i];
    Node u = nodes[edge.sourceNodeArrayIdx];
    Node v = nodes[edge.targetNodeArrayIdx];

    if (edge.sourceNodeArrayIdx == edge.targetNodeArrayIdx)
    {
      continue;
    }

    float vecX = v.x - u.x;
    float vecY = v.y - u.y;
    float vecLength = sqrt(vecX * vecX + vecY * vecY);
    float common = (vecLength * vecLength) / k;
    displacements[edge.targetNodeArrayIdx].x -= (vecX / vecLength) / common;
    displacements[edge.targetNodeArrayIdx].y -= (vecY / vecLength) / common;
    displacements[edge.sourceNodeArrayIdx].x += (vecX / vecLength) * common;
    displacements[edge.targetNodeArrayIdx].y += (vecY / vecLength) * common;
  }
}

void calCluster(const Node *nodes, const size_t nodeSize, const Cluster *clusters, const size_t clusterSize, Point *displacements, const float clusterGravity, const float k)
{
  for (size_t i = 0; i < clusterSize; i++)
  {
    Cluster c = clusters[i];
    for (size_t j = 0; j < c.nodeSize; j++)
    {
      Node n = nodes[c.nodeArrayIdx[j]];
      float distLength = sqrt((n.x - c.cx) * (n.x - c.cx) + (n.y - c.cy) * (n.y - c.cy));
      float gravityForce = k * clusterGravity;

      displacements[j].x -= (gravityForce * (n.x - c.cx)) / distLength;
      displacements[j].y -= (gravityForce * (n.y - c.cy)) / distLength;
    }
  }
}

void calGravity(Node *nodes, size_t nodeSize, Point *displacements, float gravity, float k, Center *center)
{
  for (size_t i = 0; i < nodeSize; i++)
  {
    Node n = nodes[i];
    float gravityForce = 0.01 * k * gravity;

    displacements[i].x -= gravityForce * (n.x - center->x);
    displacements[i].y -= gravityForce * (n.y - center->y);
  }
}

void createRandNodes(Node *nodes, size_t count, short width, short height)
{
  srand(time(NULL));
  for (size_t i = 0; i < count; i++)
  {
    nodes[i].x = rand() % width;
    nodes[i].y = rand() % height;
  }
}

void createRandEdges(Edge *edges, size_t count, size_t nodeSize)
{
  srand(time(NULL));
  for (size_t i = 0; i < count; i++)
  {
    edges[i].sourceNodeArrayIdx = rand() % nodeSize;
    edges[i].targetNodeArrayIdx = rand() % nodeSize;
  }
}

int main()
{
  using namespace std;

  const size_t nodeNum = 8323;
  const size_t edgeNum = 5421;
  // int SPEED_DIVISOR = 800;

  float width = 1000;
  float height = 1000;
  float gravity = 10;
  float area = width * height;
  float maxDisplace = sqrt(area) / 10;
  float k2 = area / (nodeNum + 1);
  float k = sqrt(k2);
  Center center = {width / 2, height / 2};
  Point displacements[nodeNum] = {};

  // 初始化 nodes
  Node nodes[nodeNum] = {};
  Edge edges[edgeNum] = {};
  createRandNodes(nodes, nodeNum, width, height);
  createRandEdges(edges, edgeNum, nodeNum);

  cout << "nodes: " << nodeNum << endl;
  cout << "edges: " << edgeNum << endl;

  // printNodes(nodes, nodeNum);
  // printEdges(edges, edgeNum);
  // writeToFile(nodes, nodeNum);
  clock_t allstart = clock();

  clock_t start = clock();
  calRepulsive(nodes, nodeNum, displacements, k2);
  clock_t end = clock();
  cout << "calRepulsive call time: " << (end - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
  start = clock();
  calAttractive(nodes, nodeNum, edges, edgeNum, displacements, k);
  end = clock();
  cout << "calAttractive call time: " << (end - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;

  // calCluster(nodes, nodeNum, displacements, k);

  calGravity(nodes, nodeNum, displacements, gravity, k, &center);
  end = clock();
  cout << "time: " << (end - allstart) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
  return 0;
}
