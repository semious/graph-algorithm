#include <iostream>
#include <cmath>
#include "fruchterman.h"

void calculate_repulsive_force(const Node *nodes, const size_t nodeSize, Point *out, const float k)
{
  for (size_t i = 0; i < nodeSize; i++) {
    for (size_t j = 0; j < nodeSize; j++) {
      if (i == j) {
        continue;
      }
      Node v = nodes[i];
      Node u = nodes[j];
      float vec_x = v.x - u.x;
      float vec_y = v.y - u.y;
      float vec_length_square = vec_x * vec_x + vec_y * vec_y;
      if (vec_length_square < 1e-6) {
        vec_length_square = 1.0;
        float sign = i > j ? 1.f : -1.f;
        vec_x = sign * 0.01f;
        vec_y = sign * 0.01f;
      }
      float common = k / vec_length_square;
      vec_x = vec_x * common;
      vec_y = vec_y * common;

      out[i].x += vec_x;
      out[i].y += vec_y;
    }
  }
}

void calculate_attractive(const Node *nodes, const size_t nodeSize, const Edge *edges, const size_t edge_size, Point *out, const float k)
{
  for (size_t i = 0; i < edge_size; i++) {
    Edge edge = edges[i];
    Node u = nodes[edge.src_node_idx];
    Node v = nodes[edge.target_node_idx];

    if (edge.src_node_idx == edge.target_node_idx) {
      continue;
    }

    float vecX = v.x - u.x;
    float vecY = v.y - u.y;
    float vec_length_sqrt = sqrtf(vecX * vecX + vecY * vecY);
    float common = (vec_length_sqrt * vec_length_sqrt) / k;

    out[edge.target_node_idx].x -= (vecX / vec_length_sqrt) / common;
    out[edge.target_node_idx].y -= (vecY / vec_length_sqrt) / common;
    out[edge.src_node_idx].x += (vecX / vec_length_sqrt) * common;
    out[edge.src_node_idx].y += (vecY / vec_length_sqrt) * common;
  }
}

void calculate_cluster(const Node *nodes, const Cluster *clusters, const size_t clusterSize, Point *out, const float cluster_gravity, const float k)
{
  for (size_t i = 0; i < clusterSize; i++) {
    Cluster cluster = clusters[i];
    for (size_t j = 0; j < cluster.node_size; j++) {
      Node n = nodes[cluster.nodeArrayIdx[j]];

      float x_diff = n.x - cluster.cx;
      float y_diff = n.y - cluster.cy;

      float distance = sqrtf(x_diff * x_diff + y_diff * y_diff);
      float gravityForce = k * cluster_gravity;

      out[j].x -= (gravityForce * x_diff) / distance;
      out[j].y -= (gravityForce * y_diff) / distance;
    }
  }
}

void calculate_gravity(Node *nodes, size_t nodeSize, Point *out, float gravity, float k, Center *center)
{
  for (size_t i = 0; i < nodeSize; i++) {
    Node n = nodes[i];
    float gravityForce = 0.01f * k * gravity;

    out[i].x -= gravityForce * (n.x - center->x);
    out[i].y -= gravityForce * (n.y - center->y);
  }
}

