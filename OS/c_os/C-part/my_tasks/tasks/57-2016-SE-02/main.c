#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#define CHECK_ERR(result_code,err_code,message) if(result_code == -1){ err(err_code,message);}

struct pr{
	uint32_t x;
	uint32_t y;
}__attribute__((packed));

int main(int argc, char ** argv){
	
	if(argc!=3){
		errx(1,"Wrong usage!Expected 2 arguments, got (%d)",argc-1);
	}
	
	int f1 = open(argv[1],O_RDONLY);
	CHECK_ERR(f1,1,"Error while opening file1!")
	
	int f2 = open(argv[2],O_RDONLY);
	CHECK_ERR(f2,1,"Error while opening file2!")

	int f3 = open(argv[3],O_CREAT | O_TRUNC | O_WRONLY,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	CHECK_ERR(f3,1,"Error while opening file3")


	//check sizes
	struct stat st;
	int res = fstat(f1,&st);
	CHECK_ERR(res,2,"Error while statting file")
	
	if(st.st_size % 8 !=0){
		errx(3,"Wrong file format given for %s",argv[1]);
	}

	res = fstat(f2,&st);
	CHECK_ERR(res,2,"Error while statting file")

	if(st.size % 4 != 0){
		errx(3,"Wronng file format given for %s",argv[2]);
	}
	res = fstat(f3,&st);
	CHECK_ERR(res,2,"Error while statting file")
	int read_bytes;
	struct pr current_xy;
	while( (read_bytes = read(fd1,&current_xy,sizeof(struct pr))) == sizeof(struct pr) ){
		if(current_xy.x + current_xy.y > st.st_size){
			errx(4,"Wrong file format");
		}
		int lresult;
		lresult = lseek(fd2,current_xy.x,SEEK_SET);
		CHECK_ERR(lresult,5,"Error while lseeking")
		uint32_t number;
			for(int i = 0 ; i < current_xy.y;i++){
				read_bytes = read(fd2,&number,sizeof(number));
				CHECK_ERR(read_bytes,6,"Error while reading")
				int wbytes = write(fd3,&number,sizeof(number));
				CHECK_ERR(wbytes,7,"Error while writing")

			}

	}
	CHECK_ERR(read_bytes,4,"Error while reading");

	close(fd1);
	close(fd2);
	close(fd3);

	exit(0);
}
