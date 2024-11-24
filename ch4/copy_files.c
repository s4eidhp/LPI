#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE	46
#endif

int main(int argc, char **argv){
	int inputFd, outputFd, openFlags, feof_res;
	mode_t filePerms;
	ssize_t numRead, numWrite;
	char buf[BUF_SIZE];

	if(argc != 3 || strcmp(argv[1], "--help") == 0){
		fprintf(stderr, "[USAGE] %s old-file new-file\n", argv[0]);
		exit(-1);
	}
	/* Open input and output files */
	inputFd = open(argv[1], O_RDONLY);
	if(inputFd == -1)
		fprintf(stderr, "[ERROR] openning file %s\n", argv[1]);

	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;		/* rw-rw-rw */

	outputFd = open(argv[2], openFlags, filePerms);
	if(outputFd == -1)
		fprintf(stderr, "[ERROR] openning file %s\n", argv[2]);

	/* Transfer data until we encounter EOF or an error */
	while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
		if (write(outputFd, buf, numRead) != numRead)
			fprintf(stderr, "[ERROR] couldn't write whole buffer");

	if(numRead == -1)
		exit(-1);

	if(close(inputFd) == -1)
		fprintf(stderr, "[ERROR] close input\n");
	if(close(outputFd) == -1)
		fprintf(stderr, "[ERROR] close output\n");

	exit(EXIT_SUCCESS);
}

