#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <unistd.h>

#define CHECK_ERR(result,err_code,message) if(result == -1){ err(err_code,message);}

struct triplet {
	uint16_t offset;
	uint8_t length;
	uint8_t nused;
}__attribute__((packed));

int main(int argc,char ** argv){
	if(argc!=5){
		errx(1,"Wrong number of arguments!Expected 4, got (%d)",argc-1);
	}
	int fd1dat = open(argv[1],O_RDONLY);
	CHECK_ERR(fd1dat,2,"Error while opening file!")

	int fd1idx = open(argv[2],O_RDONLY);
	CHECK_ERR(fd1idx,2,"Error while opening file!");


	int fd2dat = open(argv[3],O_WRONLY | O_CREAT | O_TRUNC,0644);
	CHECK_ERR(fd2dat,2,"Error while opening file!");


	int fd2idx = open(argv[4],O_WRONLY | O_CREAT | O_TRUNC,0644);
	CHECK_ERR(fd2idx,2,"Error while opening file!");
	

	struct stat s ;
	int res = fstat(fd1idx,&s);
	if(res == -1){
		const int olderrno = errno;
		close(fd1idx);
		close(fd1dat);
		close(fd2idx);
		close(fd2dat);
		errno = olderrno;
		CHECK_ERR(res,2,"Error while statting");
	}
	if(s.st_size %4 !=0){
		errx(3,"Wrong file format");
	}
	res = fstat(fd1dat,&s);
	CHECK_ERR(res,2,"Error while statting");

	int bytes_read;
	int bytes_written;
	struct triplet t;
	struct triplet new;
	while( (bytes_read= (read(fd1idx,&t,sizeof(struct triplet)))) == sizeof(struct triplet)){
				if(t.offset + t.length > s.st_size){
					errx(4,"Wrong file format");
				}
				lseek(fd1dat,t.offset,SEEK_SET);
				char symbol;
				for(int i = 0 ; i < t.length;i++){
					bytes_read = read(fd1dat,&symbol,sizeof(symbol));
					CHECK_ERR(bytes_read,2,"Error while reading");

					if(('A' >= symbol || symbol>='Z') && i == 0){
						break;
					}
					else{		
						new.offset = lseek(fd2dat,0,SEEK_CUR);	
						new.length = t.length;
						new.nused = t.nused;
					}

					bytes_written = write(fd2dat,&symbol,sizeof(symbol));
					CHECK_ERR(bytes_written,2,"Error while writing");


				}
				bytes_written = write(fd2idx,&new,sizeof(new));
				CHECK_ERR(bytes_written,2,"Error while writing");

		}
	CHECK_ERR(bytes_read,2,"error while reading")





	exit(0);
}

