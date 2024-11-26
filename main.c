#include <stdio.h>
#include "memo.h"

int main() {
    // Initialize memory pool with 1 MB (1048576 bytes)
    init_memory_pool(1048576);

    // Test allocation and free
    void *ptr1 = my_malloc(128);
    if (ptr1 != NULL) {
        printf("Allocated 128 bytes at %p\n", ptr1);
        my_free(ptr1);
        printf("Freed block at %p\n", ptr1);
    }

    void *ptr2 = my_malloc(256);
    if (ptr2 != NULL) {
        printf("Allocated 256 bytes at %p\n", ptr2);
        my_free(ptr2);
        printf("Freed block at %p\n", ptr2);
    }

    return 0;
}
