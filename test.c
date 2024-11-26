#include <stdio.h>
#include <stdlib.h>

#include "memo.h"  // Include the header for your custom memory manager

// Test function to verify malloc behavior
void test_malloc() {
    printf("Running malloc test...\n");

    // Test allocating memory
    int* ptr = (int*)my_malloc(sizeof(int));
    if (ptr == NULL) {
        printf("Test failed: malloc returned NULL\n");
    } else {
        *ptr = 42;  // Set a value
        printf("Test passed: allocated int with value %d\n", *ptr);
        my_free(ptr);  // Free the memory
    }
}

// Test function to verify realloc behavior
void test_realloc() {
    printf("Running realloc test...\n");

    // Allocate and set initial values
    int* ptr = (int*)my_malloc(sizeof(int) * 2);
    if (ptr == NULL) {
        printf("Test failed: malloc returned NULL\n");
        return;
    }

    ptr[0] = 42;
    ptr[1] = 84;
    printf("Test passed: initial values: %d, %d\n", ptr[0], ptr[1]);

    // Reallocate to a larger size
    ptr = (int*)my_realloc(ptr, sizeof(int) * 4);
    if (ptr == NULL) {
        printf("Test failed: realloc returned NULL\n");
    } else {
        ptr[2] = 168;
        ptr[3] = 336;
        printf("Test passed: realloc success, new values: %d, %d, %d, %d\n",
               ptr[0], ptr[1], ptr[2], ptr[3]);
        my_free(ptr);  // Free the memory
    }
}

// Test function to verify free behavior
void test_free() {
    printf("Running free test...\n");

    // Allocate and free multiple blocks
    int* ptr1 = (int*)my_malloc(sizeof(int));
    int* ptr2 = (int*)my_malloc(sizeof(int));

    if (ptr1 != NULL && ptr2 != NULL) {
        *ptr1 = 100;
        *ptr2 = 200;

        printf("Test passed: allocated two blocks with values %d and %d\n",
               *ptr1, *ptr2);

        // Free the memory
        my_free(ptr1);
        my_free(ptr2);
        printf("Test passed: freed both blocks\n");
    } else {
        printf("Test failed: malloc returned NULL\n");
    }
}

int main(int argc, char* argv[]) {
    // Initialize memory pool with a fixed size (e.g., 1024 bytes)
    init_memory_pool(1024);

    // Run the tests
    test_malloc();
    test_realloc();
    test_free();

    return 0;
}
