#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <err.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#define CHECK_ERR(result,err_code,message) if(result == -1){err(err_code,message);}
int main(int argc,char ** argv){

	if(argc!=3){
		errx(1,"Wrong number of arguments!Expected 2 , got (%d) instead",argc-1);
	}
	int times = atoi(argv[1]);
	int pfd1[2];
	int pfd2[2];
	int result = pipe(pfd1);
    CHECK_ERR(result,2,"Error while piping");
	result = pipe(pfd2);
	CHECK_ERR(result,2,"Error while piping");
    pid_t pid = fork();
    CHECK_ERR(pid,3,"Error while forking");
    if(pid ==0){
	//child (pfd1 is from parent to child)
		close(pfd1[1]);
		close(pfd2[0]);
		uint8_t byte;
		int bytes_read;
		while((bytes_read = read(pfd1[0],&byte,sizeof(byte))) == sizeof(byte)){
			int w_res = write(1,"DONG\n",5);
			CHECK_ERR(w_res,3,"Error while writing");

			//signal parent
			w_res =write(pfd2[1],"r",1);
			CHECK_ERR(w_res,3,"Error while writing");
	
		}
		CHECK_ERR(bytes_read,3,"Error while reading");
		close(pfd2[1]);
		close(pfd1[0]);


    }
	else{
	//parent
		close(pfd2[1]);
		close(pfd1[0]);
		int w_res = write(1,"DING ",5);
		CHECK_ERR(w_res,3,"Error while writing");
		w_res = write(pfd1[1],"r",1);
		CHECK_ERR(w_res,3,"Error while writing");
		times--;
		int bytes_read;
		uint8_t byte;
		while( (bytes_read = read(pfd2[0],&byte,sizeof(byte)) == sizeof(byte)) && times>=1 ){
			times--;
			sleep(atoi(argv[2]));
			int s_res = write(1,"DING ",5);
			CHECK_ERR(s_res,3,"Error while writing");
			
			//signal child
			s_res = write(pfd1[1],"r",1);
			CHECK_ERR(s_res,3,"Error while writing");

		}
		CHECK_ERR(bytes_read,3,"Error while reading");
		sleep(atoi(argv[2]));
		close(pfd1[1]);
		close(pfd2[0]);
		wait(NULL);
	}

	exit(0);
}
