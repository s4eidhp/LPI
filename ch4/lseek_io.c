#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv){

	long len;
	char *buffer;
	int numRead, i;

	if(argc < 2){
		printf("Usage: %s file {r<length> | R<length> | s<offset> | w<str>} ...\n", argv[0]);
		exit(-1);
	}

	/* open file */
	int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if(fd == -1){
		printf("can not open file\n");
		exit(-1);
	}

	for(int ap = 2; ap < argc; ap++){
		switch(argv[ap][0]){
			case 'r':	/* display length bytes in text format */
			case 'R':	/* display length bytes in hexadecimal format */
				len = strtol(&argv[ap][1], NULL, 10);
				buffer = malloc(len);
				numRead = read(fd, buffer, len);

				if(numRead == 0){
					printf("%s end of file\n", argv[ap]);
				}else{
					if(argv[ap][0] == 'r')
						for(i = 0; i < numRead; i++)
							printf("%c", isprint((unsigned char)buffer[i]) ? buffer[i] : '?');
					else
						for(i = 0; i < numRead; i++)
							printf("%02x ", (unsigned int)buffer[i]);
					printf("\n");
				}

				free(buffer);
				break;

			case 's':	/* seek to byte offset from start of the file */
				len = strtol(&argv[ap][1], NULL, 10);
				lseek(fd, len, SEEK_SET);
				printf("seek succeeded!\n");
				break;

			case 'w':	/* write string at current offset */
				write(fd, &argv[ap][1], strlen(&argv[ap][1]));
				printf("write was successful\n");
				break;

			default:
				printf("Invalid command!\n");
				exit(-1);

		}
	}

	exit(EXIT_SUCCESS);
}
