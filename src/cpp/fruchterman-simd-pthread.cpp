#include <iostream>
#include <cmath>
#include <ctime>
#include <xmmintrin.h>
#include <pthread.h>
#include "fruchterman.h"

struct VectorDis
{
  float x[4];
  float y[4];
};

void _calRepulsiveForceBySIMD(__m128 vx_mm, __m128 vy_mm, __m128 sign, float k2, VectorDis *ret)
{
  __m128 vecLengthSqr = _mm_add_ps(_mm_mul_ps(vx_mm, vx_mm), _mm_mul_ps(vy_mm, vy_mm));
  // __m128 vecZeros = _mm_setzero_ps();
  // __m128 cmpRet = _mm_cmpgt_ps(vecLengthSqr, vecZeros);
  // for (size_t i = 0; i < 4; i++)
  // {
  //   // vecLengthSqr 某个分量为 0
  //   if (cmpRet[i] < 1e-6)
  //   {
  //     vecLengthSqr[i] = 1.0f;
  //     vx_mm[i] = sign[i] * 0.01;
  //     vy_mm[i] = sign[i] * 0.01;
  //   }
  // }
  __m128 common = _mm_div_ps(_mm_set1_ps(k2), vecLengthSqr);
  vx_mm = _mm_mul_ps(vx_mm, common);
  vy_mm = _mm_mul_ps(vy_mm, common);

  _mm_storeu_ps(ret->x, vx_mm);
  _mm_storeu_ps(ret->y, vy_mm);
}

/**
 * @brief 为了提高效率，使用 SSE 指令，并且nodes的数量为4的倍数
 * 
 * @param nodes 
 * @param nodeSize 
 * @param displacements 
 * @param k2 
 */
void calRepulsive2(const Node *nodes, const size_t nodeSize, Point *displacements, const float k2)
{
  _MM_ALIGN16 float vx[4];
  _MM_ALIGN16 float vy[4];
  _MM_ALIGN16 float sign[4];
  __m128 vx_mm = _mm_setzero_ps();
  __m128 vy_mm = _mm_setzero_ps();
  __m128 sign_mm = _mm_setzero_ps();
  Point ret[4] = {0};
  VectorDis vecDis = {};
  int k;

  for (size_t i = 0; i < nodeSize; i++)
  {
    for (size_t j = 0; j < nodeSize; j += 4)
    {

      for (k = 0; k < 4; k++)
      {
        vx[k] = nodes[i].x - nodes[j + k].x;
        vy[k] = nodes[i].y - nodes[j + k].y;
        sign[k] = (i > (j + k)) ? 1.0f : -1.0f;
      }

      vx_mm = _mm_load_ps(vx);
      vy_mm = _mm_load_ps(vy);
      sign_mm = _mm_load_ps(sign);

      _calRepulsiveForceBySIMD(vx_mm, vy_mm, sign_mm, k2, &vecDis);

      // displacements[i].x += vecDis.x[j] + vecDis.x[j+1] + vecDis.x[j+2] + vecDis.x[j+3];
      // displacements[i].y += vecDis.y[j] + vecDis.y[j+1] + vecDis.y[j+2] + vecDis.y[j+3];
      // for (k = 0; k < 4; k++)
      // {
      //   // 如果是同一个点，则不计算
      //   if (i == (j + k))
      //   {
      //     continue;
      //   }
      //   displacements[i].x += ret[k].x;
      //   displacements[i].y += ret[k].y;
      // }
    }
  }
}

struct ThreadData
{
  size_t from;
  size_t to;
  Node *nodes;
  size_t nodeSize;
  Point *displacements;
  float k2;
};

void calRepulsiveByRange(const int from, const int to, const Node *nodes, size_t nodeSize, Point *displacements, const float k2)
{
  // std::cout << "from: " << from << " to: " << to << std::endl;
  clock_t start = clock();
  // std::cout << "time start: " << start << std::endl;
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
  std::cout <<  "from: " << from << " to: " << to << " time end: " << clock() - start << std::endl;
}

void calRepulsiveByRange2(const int from, const int to, const Node *nodes, size_t nodeSize, Point *displacements, const float k2)
{
  // std::cout << "from: " << from << " to: " << to << std::endl;
  clock_t start = clock();
  // std::cout << "time start: " << start << std::endl;
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
  std::cout <<  "from: " << from << " to: " << to << " time end: " << clock() - start << std::endl;
}

void *dispatchCalRepulsive(void *argv)
{
  using namespace std;
  ThreadData *data = (ThreadData *)argv;
  clock_t start = clock();
  calRepulsiveByRange(data->from, data->to, data->nodes, data->nodeSize, data->displacements, data->k2);
  // cout << "from " << data->from << " to " << data->to << endl;
  clock_t end = clock();
  cout << "thread 1 " << pthread_self() << " cost " << (end - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
  // pthread_exit(NULL);
}
void *dispatchCalRepulsive2(void *argv)
{
  using namespace std;
  ThreadData *data = (ThreadData *)argv;
  clock_t start = clock();
  calRepulsiveByRange2(data->from, data->to, data->nodes, data->nodeSize, data->displacements, data->k2);
  // cout << "from " << data->from << " to " << data->to << endl;
  clock_t end = clock();
  cout << "thread 2" << pthread_self() << " cost " << (end - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
  // pthread_exit(NULL);
}


void calRepulsiveByThreads(const Node *nodes, const size_t nodeSize, Point *displacements, const float k2)
{
  using namespace std;
  const size_t threadNum = 2;
  const size_t threadSize = nodeSize / threadNum;
  const size_t threadRemainder = nodeSize % threadNum;
  ThreadData input[threadNum] = {};
  pthread_t ptid[threadNum];

  for (size_t i = 0; i < threadNum; i++)
  {
    input[i].from = i * threadSize;
    input[i].to = (i + 1) * threadSize;
    input[i].nodes = (Node*) nodes;
    input[i].nodeSize = nodeSize;
    input[i].displacements = displacements;
    input[i].k2 = k2;
    if( i%2 == 0) {
      cout << "create thread " << i << endl;
      pthread_create(&ptid[i], NULL, dispatchCalRepulsive, &input[i]);
    }else {
      cout << "create thread2 " << i << endl;
      pthread_create(&ptid[i], NULL, dispatchCalRepulsive2, &input[i]);
    }
  }
  
  calRepulsiveByRange(threadNum * threadSize, nodeSize, nodes, nodeSize, displacements, k2);

  // pthread_join(ptid, NULL);
  for (size_t i = 1; i < threadNum; i++)
  {
    pthread_join(ptid[i], NULL);
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
  cout << "calRepulsive call time: " << (end - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
  // cout << "displacements " << displacements[0].x << " " << displacements[0].y << endl;
  // cout << "displacements " << displacements[1].x << " " << displacements[1].y << endl;

  // displacements reset 0
  // for (size_t i = 0; i < nodeNum; i++)
  // {
  //   displacements[i].x = 0;
  //   displacements[i].y = 0;
  // }

  clock_t start2 = clock();
  calRepulsiveByThreads(nodes, nodeNum, displacements, k2);
  clock_t end2 = clock();
  cout << "calRepulsiveByThreads call time: " << (end2 - start2) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
  // cout << "displacements " << displacements[0].x << " " << displacements[0].y << endl;
  // cout << "displacements " << displacements[1].x << " " << displacements[1].y << endl;

  start = clock();
  calAttractive(nodes, nodeNum, edges, edgeNum, displacements, k);
  end = clock();
  cout << "calAttractive call time: " << (end - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;

  // calCluster(nodes, nodeNum, displacements, k);

  calGravity(nodes, nodeNum, displacements, gravity, k, &center);
  end = clock();
  cout << "time: " << (end - allstart) / (double)CLOCKS_PER_SEC * 1000<< " ms" << endl;
  return 0;
}
