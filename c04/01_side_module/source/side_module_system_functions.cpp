#include <emscripten.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

const int TOTAL_MEMORY = 65536;
const int MAXIMUM_ALLOCATED_CHUNKS = 10;

int current_allocated_count = 0;

struct MemoryAllocated {
  int offset;
  int length;
};

struct MemoryAllocated AllocatedMemoryChunks[MAXIMUM_ALLOCATED_CHUNKS];

void InsertIntoAllocatedArray(int new_item_index, int offset_start,
                              int size_needed) {
  for (int i = (MAXIMUM_ALLOCATED_CHUNKS - 1); i > new_item_index; i--) {
    AllocatedMemoryChunks[i] = AllocatedMemoryChunks[(i - 1)];
  }
  AllocatedMemoryChunks[new_item_index].offset = offset_start;
  AllocatedMemoryChunks[new_item_index].length = size_needed;
  current_allocated_count++;
}

EMSCRIPTEN_KEEPALIVE
int create_buffer(int size_needed) {
  if (current_allocated_count == MAXIMUM_ALLOCATED_CHUNKS) {
    return 0;
  }
  int offset_start = 1025;
  int current_offset = 0;
  int found_room = 0;

  int memory_size = size_needed;
  while (memory_size % 8 != 0) {
    memory_size++;
  }

  for (int index = 0; index < current_allocated_count; index++) {
    current_offset = AllocatedMemoryChunks[index].offset;
    if ((current_offset - offset_start) >= memory_size) {
      InsertIntoAllocatedArray(index, offset_start, memory_size);
      found_room = 1;
      break;
    }
    offset_start = (current_offset + AllocatedMemoryChunks[index].length);
  }

  if (found_room == 0) {
    if (((TOTAL_MEMORY - 1) - offset_start) >= size_needed) {
      AllocatedMemoryChunks[current_allocated_count].offset = offset_start;
      AllocatedMemoryChunks[current_allocated_count].length = size_needed;
      current_allocated_count++;
      found_room = 1;
    }
  }

  if (found_room == 1) {
    return offset_start;
  }
  return 0;
}

void free_buffer(int offset);
int atoi(const char *value);

#ifdef __cplusplus
}
#endif
