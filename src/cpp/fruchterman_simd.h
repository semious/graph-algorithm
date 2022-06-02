#include <iostream>
#include <cmath>
#include <ctime>
#include <wasm_simd128.h>
#include "graph.h"

struct VectorDis
{
  float x[4];
  float y[4];
};

void _calRepulsiveForceBySIMD(v128_t vx_mm, v128_t vy_mm, v128_t sign, float k2, VectorDis *ret);

/**
 * @brief 为了提高效率，使用 SSE 指令，并且nodes的数量为4的倍数
 * 
 * @param nodes 
 * @param nodeSize 
 * @param displacements 
 * @param k2 
 */
void calRepulsive2(const Node *nodes, size_t nodeSize, Point *displacements, float k2);

void calRepulsive(const Node *nodes,  size_t nodeSize, Point *displacements,  float k2);


void calAttractive(const Node *nodes,  size_t nodeSize, const Edge *edges,  size_t edgeSize, Point *displacements, const float k);
void calCluster(const Node *nodes,  size_t nodeSize, const Cluster *clusters,  size_t clusterSize, Point *displacements, const float clusterGravity, const float k);

void calGravity(Node *nodes, size_t nodeSize, Point *displacements, float gravity, float k, Center *center);



