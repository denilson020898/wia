#include <emscripten.h>

int main() {
  EM_ASM(console.log("calls from em asm"));
}
