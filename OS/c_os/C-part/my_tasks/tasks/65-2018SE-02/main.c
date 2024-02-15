#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <err.h>
#include <stdlib.h>
#include <fcntl.h>

#define CHECK_ERR(result,err_code,message) if (result == -1){err(err_code,message);}
static void write_to_file(int fd,uint32_t * buffer,int size){
	int res;
	for(int i = 0;int < size/4;i++){
		res = 	write(fd,buffer+i,sizeof(uint32_t));
		CHECK_ERR(res,1,"Error while reading");
	}

}
static int comparator(const void *p1,const void *p2){
	uint32_t * v1 = (uint32_t *)p1;
	uint32_t * v2 = (uint32_t *)p2;

	return *v1-*v2;
}

int main(int argc,char ** argv){

	if(argc!=3){
		errx(1,"Wrong number of arguments!Expected 2 , got (%d)",argc-1);
	}

	int fd1 = open(argv[1],O_RDONLY);
	CHECK_ERR(fd1,2,"Error when opening file");

	int fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);
	CHECK_ERR(fd2,2,"Error when opening file")

	struct stat s;
	int res = fstat(fd1,&s);
	CHECK_ERR(res,2,"Failed to fstat");

	if(s.st_size % 4 !=0){
		errx(1,"Wrong file format");

	}
	int stop,second_stop;
	if((s.st_size/2)%4 == 0){
		stop = s.st_size/2;
		second_stop = s.st_size-stop;
	}
	else{
		stop = s.st_size/2 + 2;
		second_stop = s.st_size-stop;
	}
	int total_numbers = s.st_size/4;
	int numbers1 = stop/4;
	int numbers2 = total_numbers - stop/4;
	uint32_t * buffer= (uint32_t*)malloc(stop);
	int res = read(fd1,buffer,stop);
	
	CHECK_ERR(res,1,"Error while reading");
	
	int tmp1 = open("tmp1",O_RDWR | O_CREAT | O_TRUNC,0644);
	CHECK_ERR(tmp1,1,"Error while opening file");
	int tmp1 = open("tmp1",O_RDWR | O_CREAT | O_TRUNC,0644);
	CHECK_ERR(tmp2,1,"Error while opening file");
	
	qsort(buffer,stop,sizeof(uint32_t),comparator);
	write_to_file(tmp1,buffer,stop);

	free(buffer);

	buffer = (uint32_t*)malloc(second_stop);

	int res = read(fd1,buffer,second_stop);
	
	CHECK_ERR(res,1,"Error while reading");
	
	qsort(buffer,second_stop,sizeof(uint32_t),comparator);
	write_to_file(tmp2,buffer,second_stop);

	Ãfree(buffer);

	uint32_t left_side;
	uint32_t right_side;
	int sk = lseek(tmp1,0,SEEK_SET);
	CHECK_ERR(sk,1,"error while seeking");
	sk = lseek(tmp2,0,SEEK_SET);
	CHECK_ERR(sk,1,"Error while seeking");
	int res  = read(tmp1,&left_side,sizeof(left_side));
	CHECK_ERR(res,1,"Error while reading");
	int res  = read(tmp2,&right_side,sizeof(right_side));
	CHECK_ERR(res,1,"Error while reading");
	int ended_first = -1;
	while(true){
		if(left_side < right_side){
			write(fd3,&left_side,sizeof(uint32_t));
			res = read(tmp1,&left_side,sizeof(uint32_t));
			if(res == 0){
				ended = 1;
				break;
			}

		}
		if(right_side <= left_side){
			write(fd3,&right_side,sizeof(uint32_t));
			res = read(tmp2,&right_side,sizeof(uint32_t));
			if(res == 0){
				ended = 2;
				break;

			}
		}
		
	
	}

	int bytes_read;
	if(ended ==  1){
		write(fd3,&right_side,sizeof(uint32_t));
		while((read_bytes = read(tmp2,&right_side,sizeof(right_side))) == sizeof(uint32_t)){
					write(fd3,&right_side,sizeof(uint32_t));
		}
		CHECK_ERR(read_bytes,1,"Error while reading");
	}


	if(ended ==  2){
		write(fd3,&left_side,sizeof(uint32_t));
		while((read_bytes = read(tmp1,&left_side,sizeof(left_side))) == sizeof(uint32_t)){
					write(fd3,&left_side,sizeof(uint32_t));
		}
		CHECK_ERR(read_bytes,1,"Error while reading");
	}







	exit(0);
}
