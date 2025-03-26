#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef unsigned long int   INTERNAL_SIZE_T;

struct malloc_chunk {

  INTERNAL_SIZE_T      mchunk_prev_size;  /* Size of previous chunk (if free).  */
  INTERNAL_SIZE_T      mchunk_size;       /* Size in bytes, including overhead. */

  struct malloc_chunk* fd;         /* double links -- used only if free. */
  struct malloc_chunk* bk;

  /* Only used for large blocks: pointer to next larger size.  */
  struct malloc_chunk* fd_nextsize; /* double links -- used only if free. */
  struct malloc_chunk* bk_nextsize;
};

int main() {
    void* p = malloc(140);
    if (p == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }
    printf("start address of the allocation %p\n", p);

    struct malloc_chunk* chunk = (struct malloc_chunk*) ((char*) p - 2 * sizeof(size_t));
    printf("Chunk address: %p\n", chunk);
    printf("Chunk size: %zu\n", chunk->mchunk_size);
    printf("Prev chunk size: %zu\n", chunk->mchunk_prev_size);
    printf("Start address: %p\n", (char*) chunk + 2 * sizeof(size_t));
    printf("Length of allocation: %zu bytes\n", chunk->mchunk_size - 2 * sizeof(size_t));
    return 0;
}
