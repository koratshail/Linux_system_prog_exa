#include <stdio.h>
#include <stdlib.h>
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
	off_t inoff = 0;

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
	while ((numRead = pread(inputFd, buf, BUF_SIZE, inoff)) > 0){
		if (pwrite(outputFd, buf, numRead, inoff) != numRead) {
			perror("write ");
			exit(1);
		}
		inoff = inoff + numRead + 1;
	}
	if (numRead == -1) {
		perror("read: ");
		exit(1);
	}

	close(inputFd);
	close(outputFd);

	return 0;
}
