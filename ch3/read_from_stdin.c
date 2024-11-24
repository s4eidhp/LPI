#include <stdio.h>
#include <unistd.h>

#define MAX_READ 20

int main(int argc, char **argv){
	char buff[MAX_READ];
	if(read(STDIN_FILENO, buff, MAX_READ) == -1)
		printf("Error occurd!\n");
	printf("Entered string: %s\n", buff);
	return 0;
}
