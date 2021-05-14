#include <emscripten.h>

EM_JS(
    void,
    NoReturnValueWithStringParameter,
    (const char* string_pointer),
    {
      console.log("NoReturnValueWithStringParameter ->", Module.UTF8ToString(string_pointer) );
    }
    )

int main() {
  NoReturnValueWithStringParameter("bruh is here.");
  return 0;
}
