#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

#define BUF_SIZE 256


int main(int argc, char *argv[])
{
	if (argc !=3)
	{
		printf(1, "please input the command as [mv src_file dest_file]\n");
		exit();
	}
	
	int fd_src = open(argv[1], O_RDONLY);
	if (fd_src == -1)
	{
		printf(1, "open source file failed\n");
		exit();
	}

	int fd2;
	if((fd2 = open(argv[2], O_CREATE | O_RDWR)) < 0){
		printf(1, "cannot open\n");
//		exit();
	}
	
	struct stat st;
	struct stat st2;
	fstat(fd_src, &st);
	fstat(fd2, &st2);
	
	if (st.type == T_DIR)
	{
		printf(1, "source file is a directory, cannot copy directory\n");
		exit();
	}

	else if (st.type == T_FILE && (fd2 < 0))
{
	close(fd2);
//	printf(1, "Masuke ke file & dir\n");
	char com[128] = {};
	int len1 = strlen(argv[1]);
	int len2 = strlen(argv[2]);
//	printf(1, "%c %c panjang=%d\n",argv[2][len2-1], argv[2][len2],len2);
	if (argv[2][len2-1] != '/'){
		char new2[128]= {};
		strcpy(new2,argv[2]);
		new2[len2] ='/';
//		printf(1,"newd %s\n",new2);	
		strcpy(com,new2);
//	printf(1, "destifsatu = %s\n",com);

			int i = len1 - 1;
			for (; i >= 0; i--)
				if (argv[1][i] == '/')
					break;
			i++;
			strcpy(&com[++len2], &argv[1][i]);
//			printf(1, "destifsatu = %s\n",com);
//		printf(1, "destifsatu = %s\n",com);
	}
	
	else if (argv[2][len2-1] == '/')
	{
		strcpy(com, argv[2]);
		int i = len1 - 1;
		for (; i >= 0; i--)
			if (argv[1][i] == '/')
				break;
		i++;
		strcpy(&com[len2], &argv[1][i]);
//		printf(1,"destfolder = %s\n",com);
	}
	
	int fd_dest = open(com, O_WRONLY|O_CREATE);
	if (fd_dest == -1)
	{
		printf(1, "create dest file failed\n");
		exit();
	}
	
	char buf[BUF_SIZE] = {};
	int len = 0;
	while((len = read(fd_src, buf, BUF_SIZE)) > 0)
		write(fd_dest, buf, len);
	
	close(fd_src);
	close(fd_dest);
	
	if(unlink(argv[1]) < 0)
		printf(1, "delete source file failed\n");
	
	exit();
}

	else if (st.type == T_FILE && st2.type == T_FILE && fd2>=0)
	{
		close(fd2);
//		printf(1, "Masuk ke file & file\n");
		int fd_dest;
		if ( (fd_dest = open (argv[2], O_CREATE | O_RDWR) ) < 0){
			printf(1, "mv: cannot open dest %s\n",argv[2]);
			exit();
		}
		char buf[BUF_SIZE] = {};
		int len = 0;
		while((len = read(fd_src, buf, BUF_SIZE)) > 0)
			write(fd_dest, buf, len);
		close (fd_src); close (fd_dest);

		if(unlink(argv[1]) < 0)
		printf(1, "delete source file failed\n");
	
		exit();
	}
//	exit();
}
