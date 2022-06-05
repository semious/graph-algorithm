#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <cmath>
#include <vector>
#include "src/cpp/kernel/force.hpp"

namespace graph_algo
{
  namespace wasm
  {
    extern "C" {

#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE
#endif
    void calculateRepulsiveForce(void *node, const size_t node_size, void *out, const float k)
    {
      calculate_repulsive_force(static_cast<Node *>(node), node_size, static_cast<Node *>(out), k);
    }


    } // extern "C"
  }   // namespace wasm
} // namespace spiderjs
