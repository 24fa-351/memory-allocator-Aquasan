#ifndef MEMO_H
#define MEMO_H

#include <stddef.h>

// Define the block structure to manage memory chunks
typedef struct Block {
    size_t        size;
    struct Block* next;
} Block;

// Function declarations
void* my_malloc(size_t size);
void  my_free(void* ptr);
void* my_realloc(void* ptr, size_t new_size);
void  init_memory_pool(size_t pool_size);
void* get_me_blocks(ssize_t how_much);

#endif
