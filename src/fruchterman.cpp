#include <iostream>
#include <cmath>
#include <ctime>

#include "fruchterman.h"

void calRepulsive(Node *nodes, size_t nodeSize, Point *displacements, float k2)
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

void calAttractive(Node *nodes, size_t nodeSize, Edge *edges, size_t edgeSize, Point *displacements, float k)
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

void calCluster(Node *nodes, size_t nodeSize, Cluster *clusters, size_t clusterSize, Point *displacements, float clusterGravity, float k)
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
