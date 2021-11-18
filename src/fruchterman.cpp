#include <iostream>
// #include <graph.h>
#include <ctime>
#include "fruchterman.h"
// #include <unistd.h> linux only

void createRandmonNodes(Node *nodes, int count);

// Point displacements[];

// void applyCalculate()
const short Height = 1000;
const short Width = 1000;

void createRandmonNodes(Node *nodes, int count)
{
  // srand(time(NULL));
  for (int i = 0; i < count; i++)
  {
    nodes[i].x = arc4random() % Width;
    nodes[i].y = arc4random() % Height;
  }
}

// void test(Node *nodes)
// {
//   std::cout << "test" << std::endl;
//   // std::cout << "nodes: " << n << std::endl;
//   // std::cout << "edges: " << m << std::endl;
//   nodes[0].x = 100;
//   std::cout << "test nodes[0].x: " << nodes[0].x << std::endl;
//   std::cout << "test nodes[0].y: " << nodes[0].y << std::endl;
// }

int main()
{
  using namespace std;
  clock_t start = clock();

  const unsigned int nodeNum = 1000;

  Node nodes[nodeNum] = {};
  createRandmonNodes(nodes, nodeNum);
  clock_t end = clock();


  for (int i = 0; i < nodeNum; i++)
  {
    cout << "nodes[" << i << "] x,y: " << nodes[i].x << "," << nodes[i].y << endl;
  }

  // Node nodes[2] = {
  //     {2, 0.3},
  //     {10, 19.3}};

  // cout << "nodes " << nodes << endl;
  // // test(nodes);

  // cout << "main nodes[0].x: " << nodes[0].x << endl;
  cout << "time: " << (end - start) / (double)CLOCKS_PER_SEC * 1000 << endl;
  return 0;
}
