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
	int fd,ret;
	void *filep, *newaddr;
	
	/* create new file and fetch file desctiptor to it */
	fd = open("./mapfile",O_CREAT | O_RDWR, S_IRWXU);
	if(fd < 0){
		perror("open: \n");
		exit(1);
	}

	printf("pid %d\n",getpid());
	
	/* reserve disk blocks for new file */
	posix_fallocate(fd, 0, 8192 * 2);
	
	/*  map file cache to mmap segment of the process space */
	filep = mmap(0, (8192 * 2), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(filep == MAP_FAILED){
		printf("mapping failed\n");
		exit(2);
	}

	ret = mprotect(filep, 4096, PROT_READ | PROT_EXEC);
	if(ret  < 0){
		perror(" ");
		exit(1);
	}

	ret = mprotect(filep + 4096, 4096, PROT_READ | PROT_WRITE);
	if(ret  < 0){
		perror(" ");
		exit(1);
	}

	ret = mprotect(filep + 8192, 4096, PROT_READ);
	if(ret  < 0){
		perror(" ");
		exit(1);
	}

	ret = mprotect(filep + 12288, 4096, PROT_READ |  PROT_WRITE);
	if(ret  < 0){
		perror(" ");
		exit(1);
	}
	getchar(); 

	memset(filep+4096,'m', 4096);
	return 0;
}

