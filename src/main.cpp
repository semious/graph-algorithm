#include <iostream>
#include <fstream>
#include <cmath>

#include "fruchterman.h"

using namespace std;

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

void printNodes(Node *nodes, int count)
{
  for (int i = 0; i < count; i++)
  {
    std::cout << "Node " << i << ": " << nodes[i].x << " " << nodes[i].y << std::endl;
  }
}

void printEdges(Edge *edges, int count)
{
  for (int i = 0; i < count; i++)
  {
    std::cout << "Edge " << i << ": " << edges[i].sourceNodeArrayIdx << " " << edges[i].targetNodeArrayIdx << std::endl;
  }
}

void printPoints(Point *points, int count)
{
  for (int i = 0; i < count; i++)
  {
    std::cout << "Point " << i << ": " << points[i].x << " " << points[i].y << std::endl;
  }
}

void writeToFile(Node *nodes, int count)
{
  std::ofstream outfile;
  outfile.open("nodes.txt");
  for (int i = 0; i < count; i++)
  {
    outfile << nodes[i].x << " " << nodes[i].y << std::endl;
  }
  outfile.close();
}

int main()
{
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

  clock_t start = clock();
  calRepulsive(nodes, nodeNum, displacements, k2);
  // cout << "calRepulsive call time: " << (clock() - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
  calAttractive(nodes, nodeNum, edges, edgeNum, displacements, k);
  // cout << "calAttractive call time: " << (clock() - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;

  // calCluster(nodes, nodeNum, displacements, k);
  clock_t start3 = clock();
  calGravity(nodes, nodeNum, displacements, gravity, k, &center);
  // clock_t end = clock();
  cout << "time: " << (clock() - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
  return 0;
}
