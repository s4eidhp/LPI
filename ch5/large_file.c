#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd;
	off64_t off;

	if (argc != 3 || strcmp(argv[1], "--help") == 0)
		printf("%s pathname offset\n", argv[0]);

	fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		printf("open64 failed\n");

	off = atoll(argv[2]);
	if (lseek64(fd, off, SEEK_SET) == -1)
		printf("lseek64 failed\n");

	if (write(fd, "test", 4) == -1)
		printf("write failed\n");

	exit(EXIT_SUCCESS);
}
