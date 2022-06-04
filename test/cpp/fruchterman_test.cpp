#include "catch.hpp"

#include "src/cpp/kernel/fruchterman.h"
#include "test_util.h"

#include <cstddef>
#include <cmath>
#include <iostream>

using namespace graph_algo;
using namespace std;

TEST_CASE("fruchterman algo should work", "[algo]")
{
  const size_t node_size = 10;
  const size_t edgeNum = 10;
  // int SPEED_DIVISOR = 800;

  float width = 1000.f;
  float height = 1000.f;
  float gravity = 10.f;
  float area = width * height;
//  float maxDisplace = sqrtf(area) / 10;
  float k2 = area / (node_size + 1);
  float k = sqrtf(k2);
  Center center = {width / 2, height / 2};
  Node result[node_size] = {};

  // 初始化 nodes
  Node nodes[node_size]{};
  Edge edges[edgeNum]{};
  create_rand_nodes(nodes, node_size, width, height);
//  log_nodes(nodes, node_size);
  create_rand_edges(edges, edgeNum, node_size);
//  log_edges(edges, edgeNum);

  timing("calculate_repulsive_force", [&]() {
    calculate_repulsive_force(nodes, node_size, result, k2);
  }, 10);


  timing("calculate_attractive_force", [&]() {
    calculate_attractive_force(nodes, edges, edgeNum, result, k);
  }, 10);

  timing("calculate_displacement", [&]() {
    calculate_gravity_force(nodes, node_size, result, gravity, k, &center);
  }, 10);
}

