#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main( int argc, char *argv[])
{
	int f, i;
	if (argc < 2){
		printf(2, "Need minimum 2 arguments, Touch [files]\n");
		exit();
	}
	for (i = 1; i < argc; i++){
		if (( f = open(argv[i], O_CREATE | O_RDWR)) < 0){
			printf(1, "touch: %s failed to create\n", argv[i]);
		}
		close(f);
	}
	exit();
}
