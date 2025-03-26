#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
	int alignment;
	void *ptr;
	uintptr_t addr;

	if (argc < 2) {
		printf("Please provide an alignment size.\n");
		return 1;
	}

	alignment = atoi(argv[1]);
	ptr = malloc(100);
	if(!ptr){
		printf("malloc failed\n");
		exit(1);
	}
	
	addr = (uintptr_t) ptr;
	if (addr % alignment == 0) {
		printf("Memory is aligned.\n");
	} else {
		printf("Memory is not aligned.\n");
	}

	free(ptr);

	return 0;
}
