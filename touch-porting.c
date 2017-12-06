#include <syscall.h>
#include <xv6/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xv6/fcntl.h>

int main( int argc, char *argv[])
{
	int f, i;
	if (argc < 2){
		printf("Need minimum 2 arguments, Touch [files]\n");
		sysexit();
	}
	for (i = 1; i < argc; i++){
		if (( f = open(argv[i], O_CREAT | O_RDWR)) < 0){
			printf("touch: %s failed to create\n", argv[i]);
		}
		close(f);
	}
	sysexit();
	return 0;
}
