#include <emscripten.h>

int main() {
  EM_ASM_( {
      console.log("Hello, " + Module.UTF8ToString($0))
      }, "world~");
}
