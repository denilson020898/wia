#include <emscripten.h>

int main() {
  EM_ASM_( {
      console.log("calls from em asm with parameter: " +$0)
      }, 10);
}
