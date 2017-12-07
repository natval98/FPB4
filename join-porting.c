#include <syscall.h>
#include <stdio.h>
#include <string.h>
#include <xv6/stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <xv6/fcntl.h>

char str1 [512], str2[512];

int bandingkan(int mulai, int mulai2)
{
	int i=mulai, j = mulai2;
	int start, st2;
	for (;i< sizeof(str1) && j<sizeof(str2);i++,j++)
	{
		if (str1[i] == ' ' && str2[j] == ' '){
//			printf("There is space here in str1 %d\n",i);
			for (int y=i; y <sizeof(str1); y++) {
				if (str1[y] == '\n') {start = y+1; break;}
				printf("%c",str1[y]);
			}
			
			for (int z=j; z <sizeof(str2); z++) {
				if (str2[z] == '\n') {st2 = z+1 ; break;}
				printf("%c",str2[z]);
			}
		printf("\n");
			return bandingkan(start,st2);
			
		}
		else if (str1[i] == str2[j]) {printf("%c",str1[i]);continue;}
		else {break;}
	}
	return 0;
//	if (flag==1) return i;
//	else return 0;
}


int main(int argc, char *argv[])
{
	int fd0, fd1, n;
	
	if (argc <= 2){
		printf("Need 2 arguments! cp [From] [To]\n");
		sysexit();
	}

	if ((fd0 = open (argv[1], O_RDONLY)) < 0){
		printf("join : cannot open %s\n", argv[1]);
		sysexit();
	}

	if ((fd1 = open (argv[2], O_RDONLY)) < 0){
		printf("join: cannot open %s\n", argv[2]);
		sysexit();
	}
	
	while ( ( n = read (fd0, str1, sizeof(str1) ) ) > 0 ) {}
	while ( ( n = read (fd1, str2, sizeof(str2) ) ) > 0 ) {}

//	for (int i=0;i< sizeof(str1); i++) printf("%c",str1[i]);
//	for (int i=0;i< sizeof(str2); i++) printf("%c",str2[i]);
//	printf("\n");
	int start = 0, st2 = 0;
	int point = bandingkan(start,st2);
//	printf("point %d\n\nMULAI DISINI===\n",point);

	if (point!=0){
//		for (int x=0;x<point;x++) printf("%c",str1[x]);
/*		for (int y=point; y <sizeof(str1); y++) {
			if (str1[y] == '\n') {start = y+1; break;}
			printf("%c",str1[y]);
		}

		for (int z=point; z <sizeof(str2); z++) {
			if (str2[z] == '\n') {st2 = z+1 ; break;}
			printf("%c",str2[z]);
		}
*/
		printf("\n");
	}

//	point = bandingkan(start,st2);
//	printf("start %d Point %d\n",start,point);
	
	close(fd0); close(fd1);
	sysexit();
	return 0;
}
