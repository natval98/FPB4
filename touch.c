#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {

	int i;
	
	argc -= optind;
	argv += optind;

	for (i = 0; *argv; ++argv)
	{	
		int fd = open(*argv, O_WRONLY | O_CREAT, DEFFILEMODE);

		if (fd != -1){
			close (fd);
			i = 1;
			continue;
		}
	}
    return 0;
}
