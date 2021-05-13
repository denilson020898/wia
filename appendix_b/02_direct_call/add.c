#include <emscripten.h>
#include <stdlib.h>

EMSCRIPTEN_KEEPALIVE
int Add(int value1, int value2) { return (value1 + value2); }


