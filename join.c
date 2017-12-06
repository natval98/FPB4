#include "fcntl.h"
#include "types.h"
#include "stat.h"
#include "user.h"

char str1 [512], str2[512];

int bandingkan()
{
	int i;
	for (i=0;i< sizeof(str1) && i<sizeof(str2);i++)
	{
		if (str1[i] == ' ' && str2[i] == ' '){
			return i;
		}
		else if (str1[i] == str2[i]) {continue;}
		else {break;}
	}
	return 0;
}


int main(int argc, char *argv[])
{
	int fd0, fd1, n;
	
	if (argc <= 2){
		printf(1,"Need 2 arguments! join [file1] [file2]\n");
		exit();
	}

	if ((fd0 = open (argv[1], O_RDONLY)) < 0){
		printf(1, "join : cannot open %s\n", argv[1]);
		exit();
	}

	if ((fd1 = open (argv[2], O_RDONLY)) < 0){
		printf(1, "join: cannot open %s\n", argv[2]);
		exit();
	}
	
	while ( ( n = read (fd0, str1, sizeof(str1) ) ) > 0 ) {}
	while ( ( n = read (fd1, str2, sizeof(str2) ) ) > 0 ) {}

	int point = bandingkan();

	if (point!=0){
		for (int x=0;x<point;x++) printf(1, "%c",str1[x]);
		for (int y=point; y <sizeof(str1); y++) {
			if (str1[y] == '\n') break;
			printf(1,"%c",str1[y]);
		}
		for (int z=point; z <sizeof(str2); z++) {
			if (str2[z] == '\n') break;
			printf(1,"%c",str2[z]);
		}
		printf(1, "\n");
	}

	close(fd0); close(fd1);
	exit();
	return 0;
}
