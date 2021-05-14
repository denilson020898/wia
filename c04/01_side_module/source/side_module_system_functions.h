#pragma once

#ifndef SIDE_MODULE_SYSTEM_FUNCTIONS_H_
#define SIDE_MODULE_SYSTEM_FUNCTIONS_H_

#include <stdio.h>

void InsertIntoAllocatedArray(int new_item_index, int offset_start,
                              int size_needed);
int create_buffer(int size_needed);
void free_buffer(int offset);
int atoi(const char* value);
char *strcpy(char *destination, const char *source);
size_t strlen(const char *value);

#endif
