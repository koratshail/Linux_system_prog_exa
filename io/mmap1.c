#define _GNU_SOURCE
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	int fd;
	void *filep, *newaddr;
	
	/* create new file and fetch file desctiptor to it */
	fd = open("./mapfile2",O_CREAT | O_RDWR, S_IRWXU);
	if(fd < 0){
		perror("open: \n");
		exit(1);
	}

	printf("pid %d\n",getpid());
	
	/* reserve disk blocks for new file */
	posix_fallocate(fd, 0, 8192 * 2);
	
	/*  map file cache to mmap segment of the process space */
	filep = mmap(0, 8192, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(filep == MAP_FAILED){
		printf("mapping failed\n");
		exit(2);
	}

	printf("mapped virtual address %p\n",filep);
	close(fd);
	/* access file cache through mapped pointer */
	memset(filep, 'm', 8192);

	getchar();

	/*adjusting current map to 4k */
	newaddr = mremap(filep, (size_t)8192, (size_t)4*4096, MREMAP_MAYMOVE);
	printf("mapped virtual address %p\n",newaddr);
	getchar();

	/* unmap file from the address space */
	munmap(newaddr, 8192 * 2);
	return 0;
}

