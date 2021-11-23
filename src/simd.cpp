#include <iostream>
#include <ctime>
#include <wasm_simd128.h>

#include <xmmintrin.h>

using namespace std;

int main(){
  cout.setf(ios::fixed);
  clock_t start = clock();
  __m128 v0 = _mm_set1_ps(1.0f);
  __m128 v1 = _mm_set_ps(5.0f, 6.0f, 7.0f, 8.0f);

  __m128 result = _mm_sub_ps(v0, v1);
  clock_t end = clock();
  cout << "v0[0]" << v0[0] << endl;
  cout << "time: " << (end - start) << endl;

  // start = clock();
  // float a[4] = {1.0f, 2.0f, 3.0f, 4.0f};
  // float b[4] = {5.0f, 6.0f, 7.0f, 8.0f};
  // float c[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  // for (int i = 0; i < 4; i++) {
  //   c[i] = a[i] + b[i];
  // }
  // end = clock();
  // cout << "time: " << (end - start) << endl;

  cout << result[0] << " " << result[1] << " " << result[2] << " " << result[3] << endl;
}
