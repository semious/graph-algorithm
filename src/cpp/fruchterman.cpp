#include <iostream>
#include <cmath>
#include "fruchterman.h"

void calRepulsive(const Node *nodes, const size_t nodeSize, Point *displacements, const float k2)
{
  for (size_t i = 0; i < nodeSize; i++) {
    for (size_t j = 0; j < nodeSize; j++) {
      if (i == j) {
        continue;
      }
      Node v = nodes[i];
      Node u = nodes[j];
      float vecX = v.x - u.x;
      float vecY = v.y - u.y;
      float vecLengthSqr = vecX * vecX + vecY * vecY;
      if (vecLengthSqr < 1e-6) {
        vecLengthSqr = 1.0;
        float sign = i > j ? 1.f : -1.f;
        vecX = sign * 0.01f;
        vecY = sign * 0.01f;
      }
      float common = k2 / vecLengthSqr;
      const float ret_x = vecX * common;
      const float ret_y = vecY * common;

      displacements[i].x += ret_x;
      displacements[i].y += ret_y;
    }
  }
}

void calAttractive(const Node *nodes, const size_t nodeSize, const Edge *edges, const size_t edgeSize, Point *displacements, const float k)
{
  for (size_t i = 0; i < edgeSize; i++) {
    Edge edge = edges[i];
    Node u = nodes[edge.sourceNodeArrayIdx];
    Node v = nodes[edge.targetNodeArrayIdx];

    if (edge.sourceNodeArrayIdx == edge.targetNodeArrayIdx) {
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
  for (size_t i = 0; i < clusterSize; i++) {
    Cluster c = clusters[i];
    for (size_t j = 0; j < c.nodeSize; j++) {
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
  for (size_t i = 0; i < nodeSize; i++) {
    Node n = nodes[i];
    float gravityForce = 0.01f * k * gravity;

    displacements[i].x -= gravityForce * (n.x - center->x);
    displacements[i].y -= gravityForce * (n.y - center->y);
  }
}

