#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>
#include <stdbool.h>
#define CHECK_ERR(result,err_code,message) if(result == -1){ err(err_code,message);}

struct patch{
	uint16_t offset;
	uint8_t original;
	uint8_t new;

}__attribute__((packed));

int main(int argc,char ** argv){

	if(argc!=4){
		errx(1,"Wrong number of arguments!Expected 3, got (%d).",argc-1);
	}

	int fd1 = open(argv[1],O_RDONLY);
	CHECK_ERR(fd1,1,"Error while opening");

	int fd2 = open(argv[2],O_RDONLY);
	CHECK_ERR(fd2,1,"Error while opening");

	int fd3 = open(argv[3],O_WRONLY | O_CREAT | O_TRUNC,0644);
	CHECK_ERR(fd3,1,"Error while opening");
	
	int bytes_read;
	struct patch curr;
	char c1,c2;
	while(true){
		bytes_read = read(fd1,&c1,sizeof(c1));
		CHECK_ERR(bytes_read,1,"Error while reading!")
		if(bytes_read == 0)
			break;

		bytes_read = read(fd2,&c2,sizeof(c2));
		CHECK_ERR(bytes_read,1,"Error while reading!");
		if(bytes_read == 0)
			break;

		if(c1 != c2){
			int offset = lseek(fd1,0,SEEK_CUR);
			CHECK_ERR(offset,1,"Error while lseeking");
			curr.offset = offset;
			curr.original = c1;
			curr.new = c2;
			int bytes_written = write(fd3,&curr,sizeof(curr));
			CHECK_ERR(bytes_written,1,"Error while writing");

		}


	}
	exit(0);

}

