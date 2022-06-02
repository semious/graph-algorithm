#include "fruchterman_simd.h"
#include <cstddef>
#include <cmath>
#include <iostream>

#include "test_util.h"
#include "graph.h"

int main()
{
  using namespace std;

  const size_t nodeNum = 8323;
  const size_t edgeNum = 2000;
  // int SPEED_DIVISOR = 800;

  // 将节点转成 4n 的倍数，这样可以使用 SSE 指令
  // 在最终处理的时候，将节点数量转成原来的大小
  // const size_t nodeNum4n = (nodeNum / 4 + 1) * 4;

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
  // cout << "nodeNum4n: " << nodeNum4n << endl;
  cout << "edges: " << edgeNum << endl;

  clock_t allstart = clock();

  clock_t start = clock();
  calRepulsive(nodes, nodeNum, displacements, k2);
  clock_t end = clock();
  cout << "calRepulsive call time: " << double(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
  // cout << "displacements " << displacements[0].x << " " << displacements[0].y << endl;
  // cout << "displacements " << displacements[1].x << " " << displacements[1].y << endl;

  // displacements reset 0
  // for (size_t i = 0; i < nodeNum; i++)
  // {
  //   displacements[i].x = 0;
  //   displacements[i].y = 0;
  // }

  // cout << "displacements " << displacements[0].x << " " << displacements[0].y << endl;
  // cout << "displacements " << displacements[1].x << " " << displacements[1].y << endl;

  start = clock();
  calAttractive(nodes, nodeNum, edges, edgeNum, displacements, k);
  end = clock();
  cout << "calAttractive call time: " << double(end - start) /CLOCKS_PER_SEC * 1000 << " ms" << endl;

  // calCluster(nodes, nodeNum, displacements, k);

  calGravity(nodes, nodeNum, displacements, gravity, k, &center);
  end = clock();
  cout << "time: " << (end - allstart) / (double)CLOCKS_PER_SEC * 1000<< " ms" << endl;
  return 0;
}
