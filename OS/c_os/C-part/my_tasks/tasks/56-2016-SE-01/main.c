#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <err.h>
#include <stdint.h>
#include <unistd.h>
#define CHECK_ERR(result_code,err_code,message) if(result_code == -1) {err(err_code,message);}

int main(int argc,char ** argv){
	
	if(argc!=2){
		errx(1,"Wrong usage of function.Expected 1 argument,got %d",argc-1);
	}
	int fd = open(argv[1],O_RDWR);
 	CHECK_ERR(fd,2,"Couldnt open file");
	
	int arr[256];
	for(int i = 0 ; i < sizeof(arr)/sizeof(arr[0]);i++){
		arr[i]=0;
	}

	int read_bytes;
	uint8_t byte;
	while( (read_bytes = read(fd,&byte,sizeof(uint8_t))) > 0 ){
		arr[byte]++;
	}
	int w_bytes;
	CHECK_ERR(read_bytes,3,"Problem hile reading");
	int result = lseek(fd,0,SEEK_SET);
	CHECK_ERR(result,4,"Problem while lseeking");
	for(uint16_t i = 0 ; i < 256;i++){
		for(int j = 0 ; j < arr[i];j++){
			uint8_t real = (uint8_t)i;
			w_bytes = write(fd,&real,sizeof(uint8_t));
			CHECK_ERR(w_bytes,3,"Problem while writing");
		}
	}
	exit(0);
}
