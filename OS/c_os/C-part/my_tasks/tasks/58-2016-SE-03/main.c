#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <err.h>
#define CHECK_ERR(result,err_code,message) if(result == -1){ err(err_code,message);}
int main(int argc, char ** argv){
	

	if(argc!=2){
		errx(1,"Wrong number of arguments!Expected 1 , got (%d).",argc-1);
	}
	
	int fd1 = open(argv[1],O_RDWR);
	CHECK_ERR(fd1,1,"Error while reading")


	struct stat s;
	int res = fstat(fd1,&s);
	CHECK_ERR(res,1,"Error while statting")

	if(s.st_size %4 != 0){
		errx(2,"Wrong file format");
	}






}
