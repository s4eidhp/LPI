#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv){

    int flags, fd, accessMode;

    /* check for terminal arguments */
    if(argc < 2){
        printf("[Usage] %s <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* open a file in read mode */
    fd = open(argv[1], O_RDWR);

    /* get current file flags */
    flags = fcntl(fd, F_GETFL);

    /* check for file access mode */
    accessMode = flags & O_ACCMODE;
    if(accessMode == O_RDONLY || accessMode == O_RDWR)
        printf("File is readable\n");

    /* change file flags */
    flags |= O_APPEND;
    fcntl(fd, F_SETFL, flags);
    
    /* again check for file flags */
    flags = fcntl(fd, F_GETFL);
    if(flags & O_APPEND)
        printf("File append flag is set\n");

    exit(EXIT_SUCCESS);
}
