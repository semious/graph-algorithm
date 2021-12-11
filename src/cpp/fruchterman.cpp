#include <iostream>
#include <cmath>
#include "fruchterman.h"

struct VectorDis
{
  float x[4];
  float y[4];
};

void calRepulsiveByRange(const int from, const int to, const Node *nodes, size_t nodeSize, Point *displacements, const float k2)
{
  for (size_t i = from; i < to; i++)
  {
    Node v = nodes[i];
    for (size_t j = 0; j < nodeSize; j++)
    {
      if(i == j)
      {
        continue;
      }
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
      float retx = vecX * common;
      float rety = vecY * common;

      displacements[i].x += retx;
      displacements[i].y += rety;
    }
  }
}

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
      const float retx = vecX * common;
      const float rety = vecY * common;

      displacements[i].x += retx;
      displacements[i].y += rety;
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

// int main()
// {
//   using namespace std;

//   const size_t nodeNum = 8323;
//   const size_t edgeNum = 2000;
//   // int SPEED_DIVISOR = 800;

//   // 将节点转成 4n 的倍数，这样可以使用 SSE 指令
//   // 在最终处理的时候，将节点数量转成原来的大小
//   // const size_t nodeNum4n = (nodeNum / 4 + 1) * 4;

//   float width = 1000;
//   float height = 1000;
//   float gravity = 10;
//   float area = width * height;
//   float maxDisplace = sqrt(area) / 10;
//   float k2 = area / (nodeNum + 1);
//   float k = sqrt(k2);
//   Center center = {width / 2, height / 2};
//   Point displacements[nodeNum] = {};

//   // 初始化 nodes
//   Node nodes[nodeNum] = {};
//   Edge edges[edgeNum] = {};
//   createRandNodes(nodes, nodeNum, width, height);
//   createRandEdges(edges, edgeNum, nodeNum);

//   cout << "nodes: " << nodeNum << endl;
//   // cout << "nodeNum4n: " << nodeNum4n << endl;
//   cout << "edges: " << edgeNum << endl;

//   clock_t allstart = clock();

//   clock_t start = clock();
//   calRepulsive(nodes, nodeNum, displacements, k2);
//   clock_t end = clock();
//   cout << "calRepulsive call time: " << (end - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
//   // cout << "displacements " << displacements[0].x << " " << displacements[0].y << endl;
//   // cout << "displacements " << displacements[1].x << " " << displacements[1].y << endl;

//   // displacements reset 0
//   // for (size_t i = 0; i < nodeNum; i++)
//   // {
//   //   displacements[i].x = 0;
//   //   displacements[i].y = 0;
//   // }

//   start = clock();
//   calAttractive(nodes, nodeNum, edges, edgeNum, displacements, k);
//   end = clock();
//   cout << "calAttractive call time: " << (end - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;

//   // calCluster(nodes, nodeNum, displacements, k);

//   calGravity(nodes, nodeNum, displacements, gravity, k, &center);
//   end = clock();
//   cout << "time: " << (end - allstart) / (double)CLOCKS_PER_SEC * 1000<< " ms" << endl;
//   return 0;
// }
