#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE  512
#define MAX 3

/* Function to fill the iovec values */
void populate_iovec(struct iovec *iovec, char *ptr, int size)
{
	iovec->iov_base = ptr;
	iovec->iov_len = size;
}

int main()
{
	int fd, rbytes;
	char read_buf1[BUFFER_SIZE];
	char read_buf2[BUFFER_SIZE];
	char read_buf3[BUFFER_SIZE];
	char read_buf4[BUFFER_SIZE];
	struct iovec iovec[4];

	fd = open("./linux.mp4", O_RDONLY);

	populate_iovec(iovec, read_buf1, sizeof(read_buf1));
	populate_iovec(iovec + 1, read_buf2, sizeof(read_buf2));
	populate_iovec(iovec + 2, read_buf3, sizeof(read_buf3));
	populate_iovec(iovec + 3, read_buf4, sizeof(read_buf4));

	/* The  readv()  function  reads  iovcnt  buffers  from  the file 
	 *  associated with the file descriptor fd into the buffers
	 *  iov buffers 
	 *  file associated with the  file  descriptor
	 */
	rbytes = readv(fd, iovec, 4);

	printf("\n Total number of bytes read from file : %d \n", rbytes);
	printf(" %s\n", read_buf1);
	printf(" %s\n", read_buf2);
	printf(" %s\n", read_buf3);
	printf(" %s\n", read_buf4);

	close(fd);
}
