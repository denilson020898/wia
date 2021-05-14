#include <stdio.h>
#include <emscripten.h>

int main() {
  double sum = EM_ASM_DOUBLE({
      return $0 + $1;
      }, 1.1, 2.2);
  printf("Why are u running from number %f\n", sum);
}

