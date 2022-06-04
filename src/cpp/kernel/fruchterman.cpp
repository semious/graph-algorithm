#include <iostream>
#include <cmath>
#include "src/cpp/kernel/fruchterman.h"

namespace graph_algo
{
  void calculate_repulsive_force(Node *nodes, const size_t node_size, Node *out, const float k)
  {
    for (size_t i = 0; i < node_size; i++) {
      for (size_t j = 0; j < node_size; j++) {
        if (i == j) {
          continue;
        }
        auto &node_i = nodes[i];
        auto &node_j = nodes[j];
        float delta_x = node_i.x - node_j.x;
        float delta_y = node_i.y - node_j.y;
        float vec_length_square = delta_x * delta_x + delta_y * delta_y;
        if (vec_length_square < 1e-6) {
          vec_length_square = 1.0f;
          float sign = i > j ? 1.f : -1.f;
          delta_x = sign * 0.01f;
          delta_y = sign * 0.01f;
        }
        float common = k / vec_length_square;
        delta_x = delta_x * common;
        delta_y = delta_y * common;

        out[i].x += delta_x;
        out[i].y += delta_y;
      }
    }
  }

  void calculate_attractive_force(const Node *nodes, const Edge *edges, size_t edge_size, Node *out, float k)
  {
    for (size_t i = 0; i < edge_size; i++) {
      auto &edge = edges[i];

      if (edge.src_node_idx == edge.target_node_idx) {
        continue;
      }

      auto src_node_idx = edge.src_node_idx;
      auto target_node_idx = edge.target_node_idx;

      auto &node_src = nodes[src_node_idx];
      auto &node_target = nodes[target_node_idx];

      float delta_x = node_target.x - node_src.x;
      float delta_y = node_target.y - node_src.y;
      float vec_length_sqrt = sqrtf(delta_x * delta_x + delta_y * delta_y);
      float common = (vec_length_sqrt * vec_length_sqrt) / k;

      auto &out_target_node = out[target_node_idx];
      auto &out_src_node = out[src_node_idx];

      out_target_node.x -= (delta_x / vec_length_sqrt) / common;
      out_target_node.y -= (delta_y / vec_length_sqrt) / common;
      out_src_node.x += (delta_x / vec_length_sqrt) * common;
      out_src_node.y += (delta_y / vec_length_sqrt) * common;
    }
  }

  void calculate_cluster_force(const Node *nodes, const Cluster *clusters, const size_t cluster_size, Node *out, const float cluster_gravity, const float k)
  {
    for (size_t i = 0; i < cluster_size; i++) {
      Cluster cluster = clusters[i];
      for (size_t j = 0; j < cluster.node_size; j++) {
        auto &node = nodes[cluster.node_array_idx[j]];

        float delta_x = node.x - cluster.cx;
        float delta_y = node.y - cluster.cy;

        float distance = sqrtf(delta_x * delta_x + delta_y * delta_y);
        float gravityForce = k * cluster_gravity;

        out[j].x -= (gravityForce * delta_x) / distance;
        out[j].y -= (gravityForce * delta_y) / distance;
      }
    }
  }

  void calculate_gravity_force(Node *nodes, size_t node_size, Node *out, float gravity, float k, Center *center)
  {
    for (size_t i = 0; i < node_size; i++) {
      auto &node = nodes[i];
      float gravity_force = 0.01f * k * gravity;

      out[i].x -= gravity_force * (node.x - center->x);
      out[i].y -= gravity_force * (node.y - center->y);
    }
  }

}

