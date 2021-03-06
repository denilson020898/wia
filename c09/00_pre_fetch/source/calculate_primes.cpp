#include <emscripten.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <chrono>

#ifdef __cplusplus
extern "C" {
#endif

int IsPrime(int value) {
  if (value == 2) {
    return 1;
  }
  if (value <= 1 || value % 2 == 0) {
    return 0;
  }
  for (int i = 3; (i * i) <= value; i += 2) {
    if (value % i == 0) {
      return 0;
    }
  }
  return 1;
}

void FindPrimes(int start, int end, std::vector<int>& primes_found) {
  for (int i = start; i <= end; i += 2) {
    if (IsPrime(i)) {
      primes_found.push_back(i);
    }
  }
  printf("\n");
}

int main() {
  int start = 3, end = 100000;
  printf("Prime numbers between %d and %d:\n", start, end);

  std::chrono::high_resolution_clock::time_point duration_start = 
    std::chrono::high_resolution_clock::now();
  
  std::vector<int> primes_found;
  FindPrimes(start, end, primes_found);

  std::chrono::high_resolution_clock::time_point duration_end = 
    std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> duration = (duration_end - duration_start);

  printf("FindPrimes took %f milliseconds to execute\n", duration.count());
  printf("The values found:\n");
  for (int n : primes_found) {
    printf("%d ", n);
  }
  printf("\n");
  return 0;
}

#ifdef __cplusplus
}
#endif
