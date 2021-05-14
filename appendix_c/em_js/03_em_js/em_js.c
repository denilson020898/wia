#include <stdlib.h>
#include <stdio.h>
#include <emscripten.h>

EM_JS(
    char*,
    StringReturnValueWithNoParameters,
    (),
    {
      const greetings =  "bruh is returned.";
      const byteCount = (Module.lengthBytesUTF8(greetings) + 1);
      const greetinsPointer = Module._malloc(byteCount);
      Module.stringToUTF8(greetings, greetinsPointer, byteCount);
      return greetinsPointer;
    }
    );

int main() {
  char* greetinsPointer = StringReturnValueWithNoParameters();
  printf("StringReturnValueWithNoParameters called -> %s\n", greetinsPointer);
  free(greetinsPointer);
  return 0;
}
