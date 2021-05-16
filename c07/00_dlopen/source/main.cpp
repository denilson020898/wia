#include <cstdlib>

#ifdef __EMSCRIPTEN__
#include <dlfcn.h>
#include <emscripten.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*FindPrimes)(int, int);

void CalculatePrimes(const char *file_name) {
  void *handle = dlopen(file_name, RTLD_NOW);
  if (handle == NULL) {
    return;
  }
  FindPrimes findPrimes = (FindPrimes)dlsym(handle, "FindPrimes");
  if (findPrimes == NULL) {
    return;
  }
  findPrimes(3, 100000);
  dlclose(handle);
}

int main() {
  emscripten_async_wget("calculate_primes.wasm", "calculate_primes.wasm",
                        CalculatePrimes, NULL);
  return 0;
}

#ifdef __cplusplus
}
#endif
