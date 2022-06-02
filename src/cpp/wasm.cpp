#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/threading.h>
#endif

#include <cmath>
#include <vector>

namespace graph_algo_js
{
  namespace wasm
  {
    extern "C" {


//#ifdef __EMSCRIPTEN__
//    EMSCRIPTEN_KEEPALIVE
//#endif
//    void addTensor(const size_t tensor_id, void *memory_offset, const size_t size, size_t *shape, const size_t shape_size)
//    {
//      ASSERT(tensor_id > 0, "register_tensor: tensor_id must a positive number but got %d.", tensor_id);
//      ASSERT(tensor::tensor_datas.find(tensor_id) == tensor::tensor_datas.end(), "register_tensor: tensor_id %d has already been registered.", tensor_id);
//
//      tensor::tensor_datas.emplace(tensor_id, TensorData{memory_offset, size, shape, shape_size});
//    }



    } // extern "C"
  }   // namespace wasm
} // namespace spiderjs
