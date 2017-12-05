#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main( int argc, char *argv[])
{
	int f;
	if (argc < 2){
		printf(2, "Need 2 arguments, Touch [file]");
		exit();
	}
	if (( f = open(argv[1], O_CREATE | O_RDWR)) < 0){
		printf(1, "touch: %s failed to create\n", argv[1]);
	}
	close(f);
	exit();
}
