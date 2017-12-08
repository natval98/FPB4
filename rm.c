#include <syscall.h>
#include <stdio.h>
#include <string.h>


#include <xv6/stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <xv6/fcntl.h>
#include <xv6/fs.h>

int type_file (char * file)
{
  int salah=-1;
  int file=1;
  int dir=0;
  struct stat status;
  int fh; //file handler
  fh = open (file,o_RDONLY);
  if (fh <= -1) // bukan file & tidak bisa di open
  {
    return salah;
  }
  if(fstat(fd, &status) < 0) //tidak bisa dibuka dan status tidak bisa di lihat
  {
    return salah;
  }
  if (status.type == T_FILE) //target berbentuk file
  {
    return file;
  }
  else if (status.type == T_DIR) // target berbentuk folder
  {
	return dir; 
  }
  else  
    return salah;
 )

 void rekursif (char * file)
 {
 	int fg;
 	fh = open (file,0); //bisa dibuka dan diedit
 	if (fh<0) //jika tidak dapat dibuka
 	{
 		printf("cant open the file %s \n",file);
 		return
	}
	char * chscanner;// untuk melihat akhiran dari source
	struct dirent scanner;//melihat isi dari sebuah folder
	char temp_read [1024];//
	while(read(fd,&scanner,sizeof(scanner))== sizeof(scanner))
	{
		strcpy(temp_read,file);
		if (strcmp(scanner.d_name, ".") ==0 || strcmp(scanner.d_name, "..") ==0)	
			continue;
			
		chscanner= temp_read + strlen(temp_read);
    	if (*chscanner != '/') strcat(temp_read, "/"); // menambah garing apa bila di akhir tidak ada karena dapat menyebab kan error
    	
		strcat(temp_read, scanner.d_name);//menambah nama file di akhir nama alamat
    	
		int target=tipe_file (temp_read);// mengetest apa kah target berbentuk file atau folder
		
		if (target == 0)// berarti folder
		{
			rekursif(temp_read)//melakukan chek ke dalam folder;
		}
		else if (target==1)//berarti file
		{
			if(unlink(argv) < 0)
  				{
  					printf("rm: failed to delete:%s\n", argv);
  				}
			
		}
		
		else 
		{
			printf("failed to open or stat\n");
		}
    
	}
	if(unlink(file)<0)
	{
		printf ("failed to delete %s\n", temp_read);
	}
}
 
 
int main(int argc, char *argv[])
{
  int i;

  if(argc == 1 ){
    printf("Usage: rm files...\n");
    sysexit();
  }
  for(i = 1; i < argc; i++){
    if(unlink(argv[i]) < 0){
      printf("rm: %s failed to delete\n", argv[i]);
      break;
    }
  }
  sysexit();
}
