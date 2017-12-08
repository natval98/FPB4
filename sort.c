#include <syscall.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syscall.h>

int main(int argc, char *argv[])
{
    char str[256][256];
    char temp[256];
    if (argc < 2){
        printf("Usage: sort [file]\n");
        //sysexit();
    }
    else{
        int s = 0,i,j;
        FILE *fp;
        if ((fp = fopen(argv[1],"r"))==NULL) {
            fprintf(stderr,"Error: Could not open %s\n",argv[1]);
            //sysexit();
        }
        while(fgets(str[s],256,fp) !=NULL){
            s++;
        }
        for (i = 0; i < s-1; i++)       
            for (j = 0; j < s-i-1; j++) 
                if (strcmp(str[j], str[j+1])>0){
                    strcpy(temp,str[j]);
                    strcpy(str[j],str[j+1]);
                    strcpy(str[j+1],temp);
                }
        for (i=0;i<s;i++){
            printf("%s",str[i]);
        }
        fclose(fp);
    }
    //sysexit();
}
