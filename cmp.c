#include "fcntl.h"
#include "types.h"
#include "stat.h"
#include "user.h"

char str1 [512], str2[512];
int line, diff;

void comparefp()
{
	int i;
	for (i=0;i< sizeof(str1) && i<sizeof(str2);i++)
	{
		if (str1[i]=='\n') line++;
		if (str1[i] > str2[i] || str1[i] < str2[i]) {diff = i;break;}
		
	}
}

int main(int argc, char *argv[])
{
	int fd0, fd1, n;
	line = 1; diff = -1;
	
	if (argc <= 2){
		printf(1,"Need 2 arguments! cmp [file1] [file2]\n");
		exit();
	}

	if ((fd0 = open (argv[1], O_RDONLY)) < 0){
		printf(1, "cmp : cannot open %s\n", argv[1]);
		exit();
	}

	if ((fd1 = open (argv[2], O_RDONLY)) < 0){
		printf(1, "cmp: cannot open %s\n", argv[2]);
		exit();
	}

	while ( ( n = read (fd0, str1, sizeof(str1) ) ) > 0 ) {}
	while ( ( n = read (fd1, str2, sizeof(str2) ) ) > 0 ) {}

	comparefp();
	if (diff!=-1){ //berarti beda
		printf(1,"%s %s ",argv[1],argv[2]);
		printf(1,"differ: byte %d, line %d\n",diff+1,line); //karena diff pakai idx 1
	}
	//jika sama semua maka tidak perlu diprint
	close (fd0); close(fd1);
	exit();
	return 0;
}
