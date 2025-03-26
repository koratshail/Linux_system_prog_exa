#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];
	int ret;

	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		fprintf(stderr, "%s old-file new-file\n", argv[0]);
		exit(1);
	}

	/* Open input and output files */

	inputFd = open(argv[1], O_RDONLY);
	if (inputFd == -1) {
		fprintf(stderr, "error opening source file");
		exit(1);
	}


	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;	/* rw-rw-rw- */

	outputFd = open(argv[2], openFlags, filePerms);
	if (outputFd == -1) {
		fprintf(stderr, "error opening source file");
		exit(1);
	}
	getchar();

	/* Transfer data until we encounter end of input or an error */
	while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
		if (write(outputFd, buf, numRead) != numRead) {
			perror("write ");
			exit(1);
		}
	if (numRead == -1) {
		perror("read: ");
		exit(1);
	}
	close(inputFd);
	close(outputFd);

	return 0;
}

/*
 *
 * read(inputFD, buf, 1024);
 *
 * 		||
 *
 * sys_read(inputFD, buf, 1024);
 *
 * 		||
 *
 * fs_read(inputFD, buf, 1024);
 *
 *    1. lookup into files inode for specific block/blocks to be read
 *    2. lookup if required sectors/blocks were recently fetched into I/O cache.
 *    if(yes)
 *	jmp step 4
 *    3. instruct storage driver to fetch specifed data.
 *    4. move data onto application provided buffer.
 *    5. increment the file descriptors offset by number of bytes transferred.
 *
 */
