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
  struct stat status;
  int fh; //file handler
  fh = open (file,O_RDONLY);
  if (fh <= -1) // bukan file & tidak bisa di open
  {
    return -1;
  }
  if(fstat(fh, &status) < 0) //tidak bisa dibuka dan status tidak bisa di lihat
  {
    return -1;
  }
  if (status.type == T_FILE) //target berbentuk file
  {
    return 1;
  }
  else if (status.type == T_DIR) // target berbentuk folder
  {
	return 0; 
  }
  else  //apabila terjadi hal yang diluar dugaan
    return -1;
}

void deletes (char * argv)
{
    if(unlink(argv) < 0) //dihapus
  				{
  					printf("rm: failed to delete:%s\n", argv);
  				}
}

 void rekursif (char * file)
 {
 	int fh;
 	fh = open (file,0); //bisa dibuka dan diedit
 	if (fh<0) //jika tidak dapat dibuka
 	{
 		printf("cant open the file %s \n",file);
 		return;
	}
	char * chscanner;// untuk melihat akhiran dari source
	struct dirent scanner;//melihat isi dari sebuah folder
	char temp_read [1024];//sebagai alamat sementara
	while(read(fh,&scanner,sizeof(scanner))== sizeof(scanner)) 
	{
		strcpy(temp_read,file);
		if (strcmp(scanner.d_name, ".") ==0 || strcmp(scanner.d_name, "..") ==0)	
			continue;
			
		chscanner= temp_read + strlen(temp_read);
    	if (*chscanner != '/') strcat(temp_read, "/"); // menambah garing apa bila di akhir tidak ada karena dapat menyebakan 
                strcat(temp_read, scanner.d_name);//menambah nama file di akhir nama alamat
    	
		int target=type_file (temp_read);// mengetest apa kah target berbentuk file atau folder
		
		if (target == 0)// berarti folder
		{
			rekursif(temp_read);//melakukan chek ke dalam folder;
		}
		else if (target==1)//berarti file
		{
			deletes(temp_read);
		}
		
		else //jika target dituju
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
    printf("rm ?\n");
    sysexit();
  }
  
  if (strcmp(argv[1],"-rf")==0)
  {
  	//printf("delete all");
    rekursif(argv[2]);
    sysexit();
  }
  
  for(i = 1; i < argc; i++){
    if(unlink(argv[i]) < 0){
      deletes(argv[i]);
    }
  }
  sysexit();
}
