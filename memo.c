// Alex Nguyen
#include "memo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variable for the memory pool
static void*  memory_pool = NULL;
static Block* free_list = NULL;

// Initialize the memory pool
void init_memory_pool(size_t pool_size) {
    memory_pool = get_me_blocks(pool_size);
    free_list = (Block*)memory_pool;
    free_list->size = pool_size;
    free_list->next = NULL;
    printf("Memory pool initialized with %llu bytes\n", pool_size);
}

// Allocate a block of memory
void* my_malloc(size_t size) {
    Block* current = free_list;
    Block* previous = NULL;

    // Find the first block that is large enough
    while (current != NULL && current->size < size + sizeof(Block)) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return NULL;
    }

    // If the block is exactly the size we need, remove it from the free list
    if (current->size == size + sizeof(Block)) {
        if (previous == NULL) {
            free_list = current->next;
        } else {
            previous->next = current->next;
        }
    } else {
        // Otherwise, split the block
        Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
        new_block->size = current->size - (size + sizeof(Block));
        new_block->next = current->next;

        if (previous == NULL) {
            free_list = new_block;
        } else {
            previous->next = new_block;
        }

        current->size = size;
    }

    return (void*)((char*)current + sizeof(Block));
}

// Free a block of memory
void my_free(void* ptr) {
    Block* block_to_free = (Block*)((char*)ptr - sizeof(Block));

    // Add the block to the free list
    block_to_free->next = free_list;
    free_list = block_to_free;
    printf("Freed memory at address %p\n", ptr);
}

// Reallocate a block of memory
void* my_realloc(void* ptr, size_t new_size) {
    if (ptr == NULL) {
        return my_malloc(new_size);
    }

    Block* block = (Block*)((char*)ptr - sizeof(Block));
    size_t old_size = block->size;

    if (new_size == old_size) {
        return ptr;
    }

    void* new_ptr = my_malloc(new_size);
    if (new_ptr == NULL) {
        return NULL;
    }

    // Copy old data to the new block
    memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);

    my_free(ptr);
    return new_ptr;
}

// Get a block of memory from the system (simulate sbrk)
void* get_me_blocks(ssize_t how_much) {
    static char* heap_end = NULL;

    if (heap_end == NULL) {
        heap_end = (char*)malloc(how_much);
    }

    char* prev_heap_end = heap_end;
    heap_end += how_much;

    return (void*)prev_heap_end;
}
