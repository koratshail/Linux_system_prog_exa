#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

int main() {
//    setenv("MALLOC_DEBUG", "1", 1); // Enable malloc debugging
    void* ptr = malloc(16); // Allocate 16 bytes
    malloc_stats(); // Print malloc statistics

    // Deallocate the memory
    free(ptr);
    malloc_stats(); // Print malloc statistics
    return 0;
}

