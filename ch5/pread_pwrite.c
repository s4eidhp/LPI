/* This example would show how pread and pwrite functions work
 * and how use them to write into a file without changing 
 * current offset 
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define OFFSET      5
#define MAX_READ    100    

int main(int argc, char **argv){
    
    /* check for terminal args */
    if(argc < 2){
        printf("[Usage] %s <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char write_buf[] = "hello";
    char read_buf[MAX_READ];

    int fd = open(argv[1], O_RDWR);

    /* 1. read current file contents */
    int numRead;
//    numRead = read(fd, read_buf, MAX_READ);

    /* 2. write a char in a specific position */
    pwrite(fd, write_buf, strlen(write_buf), OFFSET);

    /* 3. again read file contents */
    memset(read_buf, 0, sizeof read_buf);
    numRead = read(fd, read_buf, MAX_READ);

    /* 4. read just added string */
    memset(read_buf, 0, sizeof read_buf);
    numRead = pread(fd, read_buf, MAX_READ, OFFSET);

    exit(EXIT_SUCCESS);
}
