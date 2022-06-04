
#ifndef GRAPH_ALGORITHM_TEST_UTIL_H
#define GRAPH_ALGORITHM_TEST_UTIL_H

#include "src/cpp/graph.h"

#include <ctime>
#include <random>
#include <iostream>

inline void create_random_f32(float *x_data, const float min = -10.f, const float max = 10.f)
{
  std::random_device rnd_device;
  std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
  std::uniform_real_distribution<float> dist{min, max};

//  std::cout << "create_random_f32:  x_data:" << x_data << std::endl;

  *x_data = dist(mersenne_engine);
}

inline void log_nodes(Node *nodes, size_t node_size)
{
  for (size_t i = 0; i < node_size; i++) {
    std::cout << "node[" << i << "] x:" << nodes[i].x << " y:" << nodes[i].y << std::endl;
  }
}

inline void log_edges(Edge *edges, size_t edge_size)
{
  for (size_t i = 0; i < edge_size; i++) {
    std::cout << "edge[" << i << "] from:" << edges[i].src_node_idx << " to:" << edges[i].target_node_idx << std::endl;
  }
}

inline void create_random_size_t(size_t *x_data, const size_t min = 0, const size_t max = 10)
{
  std::random_device rnd_device;
  std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
  std::uniform_int_distribution<size_t> dist{min, max};

  *x_data = dist(mersenne_engine);
}


void create_rand_nodes(Node *nodes, size_t count, float width, float height)
{
  for (size_t i = 0; i < count; i++) {
    create_random_f32(&nodes[i].x, 1, width);
    create_random_f32(&nodes[i].y, 1, height);
  }
}


void create_rand_edges(Edge *edges, size_t count, size_t node_size)
{
  for (size_t i = 0; i < count; i++) {
    create_random_size_t(&edges[i].src_node_idx, 0, node_size - 1);
    create_random_size_t(&edges[i].target_node_idx, 0, node_size - 1);
  }
}

inline void timing(const std::string &name, const std::function<void()> &func, const size_t batch_size = 10)
{
  clock_t start, end;
  start = clock();
  for (size_t i = 0; i < batch_size; ++i) {
    func();
  }

  end = clock();

  std::cout << "[benchmark] " << name << ": " << (double(end - start) / CLOCKS_PER_SEC * 1000) << " ms (" << batch_size << " count) " << std::endl;
}


#endif //GRAPH_ALGORITHM_TEST_UTIL_H
