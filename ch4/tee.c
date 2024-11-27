#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

char *read_from_stdin(){
	char *buff;
	ssize_t numRead;
	size_t total;

	buff = malloc(BUFSIZ);
	while(1){
		numRead = read(STDIN_FILENO, buff + total, BUFSIZ);
		if(numRead == -1)		/* check for correct read */
			break;
		total += numRead;
		if(total > 1 && buff[total - 1] == '\n')		/* check for EOF */
			break;

		buff = realloc(buff, total + BUFSIZ);
	}

	buff[total] = '\0';
	return buff;
}

int main(int argc, char **argv){
	
	/* check for append mode */
	bool append = false;
	int optc;
	while((optc = getopt(argc, argv, "a")) != -1){
		switch(optc){
			case 'a':
				append = true;
				break;
			default:
				exit(EXIT_FAILURE);
		}
	}

	char *data = read_from_stdin();
	
	/* print stdin into stdout */
	printf("%s", data);

	/* store data in file */
	int fd;
	if(append)
		fd = open(argv[2], O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	else
		fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	if(fd < 0)
		exit(EXIT_FAILURE);

	write(fd, data, strlen(data));
	close(fd);
	free(data);

	exit(EXIT_SUCCESS);
}

