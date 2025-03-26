#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd, i;
	unsigned char *filedata = NULL, *temp;

	fd = open("test.file", O_RDWR);

	filedata = (char *)mmap((void *)0, 4096, PROT_READ, MAP_SHARED, fd, 0);
	if (filedata == NULL) {
		perror("Maping Failed");
		exit(1);
	}
	temp = filedata;

	for (i = 0; i < 100; i++, filedata++)
		printf("%c", *filedata);

	printf("pid %d\n", getpid());

	getchar();

	mprotect(temp, 100, PROT_WRITE);

	getchar();	

	filedata -= 100;
	for (i = 0; i < 100; i++, filedata++)
		*filedata = (char)(i + 65);

	if (msync(temp, 4096, MS_SYNC) != 0)
		perror("msync : ");

	i = munmap(temp, 4096);
	if (i != 0)
		printf(" failed to unmap\n");
	return 0;
}
