#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

int main (int argc, char *argv[])
{
    int fd0, fd1, n, flag=0;
    if (argc <= 2){
        printf(1,"Need 2 arguments! mv [From] [To]\n");
        flag = 1;
        exit();
    }
    if ((fd0 = open (argv[1], O_RDONLY)) < 0){
        printf(1, "mv: cannot open %s\n", argv[1]);
        flag =1;
    }
    if ((fd1 = open (argv[2], O_CREATE|O_RDWR)) < 0){
        printf(1, "mv: cannot open %s\n", argv[2]);
        flag = 1;
    }
    
    while ( ( n = read (fd0, buf, sizeof(buf) ) ) > 0 ){
        write (fd1, buf, n );
    }
    
    if (flag == 0) unlink(argv[1]);
    close(fd0);
    close(fd1);
    exit();
}
