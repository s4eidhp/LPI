#include <stdio.h>
#include <gnu/libc-version.h>
#include <unistd.h>

int main(int argc, char **argv){
	printf("GLIBC version is: %s\n", gnu_get_libc_version());
	char buffer[10];
	confstr(_CS_GNU_LIBC_VERSION, buffer, 10);
	printf("GLIBC version is: %s\n", buffer);
	return 0;
}
