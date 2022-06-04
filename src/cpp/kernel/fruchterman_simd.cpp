#include <iostream>
#include <cmath>
#include <ctime>
#include <wasm_simd128.h>
#include "fruchterman_simd.h"
#include "graph.h"

void calculate_repulsive_force_simd(v128_t vx_mm, v128_t vy_mm, v128_t sign, float k2, VectorDis *ret)
{
  v128_t vecLengthSqr = wasm_f32x4_add(wasm_f32x4_mul(vx_mm, vx_mm), wasm_f32x4_mul(vy_mm, vy_mm));
  // __m128 vecZeros = _mm_setzero_ps();
  // __m128 cmpRet = _mm_cmpgt_ps(vecLengthSqr, vecZeros);
  // for (size_t i = 0; i < 4; i++)
  // {
  //   // vecLengthSqr 某个分量为 0
  //   if (cmpRet[i] < 1e-6)
  //   {
  //     vecLengthSqr[i] = 1.0f;
  //     vx_mm[i] = sign[i] * 0.01f;
  //     vy_mm[i] = sign[i] * 0.01f;
  //   }
  // }
  v128_t common = wasm_f32x4_div(wasm_f32x4_splat(k2), vecLengthSqr);
  vx_mm = wasm_f32x4_mul(vx_mm, common);
  vy_mm = wasm_f32x4_mul(vy_mm, common);

  wasm_v128_store(ret->x, vx_mm);
  wasm_v128_store(ret->y, vy_mm);
}

void calRepulsive2(const Node *nodes, const size_t nodeSize, Node *displacements, const float k2)
{
  float vx[4];
  float vy[4];
  float sign[4];
  v128_t vx_mm = wasm_f64x2_splat(.0f);
  v128_t vy_mm = wasm_f64x2_splat(.0f);
  v128_t sign_mm = wasm_f64x2_splat(.0f);
  Node ret[4] = {0};
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

      vx_mm = wasm_v128_load(vx);
      vy_mm = wasm_v128_load(vy);
      sign_mm = wasm_v128_load(sign);

      calculate_repulsive_force_simd(vx_mm, vy_mm, sign_mm, k2, &vecDis);

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

void calRepulsiveByRange(const int from, const int to, const Node *nodes, size_t nodeSize, Node *displacements, const float k2)
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

void calRepulsiveByRange2(const int from, const int to, const Node *nodes, size_t nodeSize, Node *displacements, const float k2)
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

void calculate_repulsive_force(const Node *nodes, const size_t nodeSize, Node *displacements, const float k2)
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

void calculate_attractive(const Node *nodes, const size_t nodeSize, const Edge *edges, const size_t edgeSize, Node *displacements, const float k)
{
  for (size_t i = 0; i < edgeSize; i++)
  {
    Edge edge = edges[i];
    Node u = nodes[edge.src_node_idx];
    Node v = nodes[edge.target_node_idx];

    if (edge.src_node_idx == edge.target_node_idx)
    {
      continue;
    }

    float vecX = v.x - u.x;
    float vecY = v.y - u.y;
    float vecLength = sqrt(vecX * vecX + vecY * vecY);
    float common = (vecLength * vecLength) / k;
    displacements[edge.target_node_idx].x -= (vecX / vecLength) / common;
    displacements[edge.target_node_idx].y -= (vecY / vecLength) / common;
    displacements[edge.src_node_idx].x += (vecX / vecLength) * common;
    displacements[edge.src_node_idx].y += (vecY / vecLength) * common;
  }
}

void calculate_cluster(const Node *nodes, const size_t nodeSize, const Cluster *clusters, const size_t clusterSize, Node *displacements, const float clusterGravity, const float k)
{
  for (size_t i = 0; i < clusterSize; i++)
  {
    Cluster c = clusters[i];
    for (size_t j = 0; j < c.node_size; j++)
    {
      Node n = nodes[c.node_array_idx[j]];
      float distLength = sqrt((n.x - c.cx) * (n.x - c.cx) + (n.y - c.cy) * (n.y - c.cy));
      float gravityForce = k * clusterGravity;

      displacements[j].x -= (gravityForce * (n.x - c.cx)) / distLength;
      displacements[j].y -= (gravityForce * (n.y - c.cy)) / distLength;
    }
  }
}

void calculate_gravity(Node *nodes, size_t nodeSize, Node *displacements, float gravity, float k, Center *center)
{
  for (size_t i = 0; i < nodeSize; i++)
  {
    Node n = nodes[i];
    float gravityForce = 0.01 * k * gravity;

    displacements[i].x -= gravityForce * (n.x - center->x);
    displacements[i].y -= gravityForce * (n.y - center->y);
  }
}



