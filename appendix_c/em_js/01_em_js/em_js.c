#include <emscripten.h>

EM_JS(
    void,
    NoReturnValueWithIntegerAndDoubleParameters,
    (int integer_value, double double_value),
    {
      console.log("NoReturnValueWithIntegerAndDoubleParameters called -> int: ", integer_value, "; double: ", double_value);
    }
    )

int main() {
  NoReturnValueWithIntegerAndDoubleParameters(69, 4.20);
  return 0;
}
