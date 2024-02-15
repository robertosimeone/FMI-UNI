#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>


#define CHECK_ERR(result,err_code,message) if(result == -1){err(err_code,message);}

int main(int argc,char ** argv){

	if(argc!=2){
		errx(1,"Wrong number of arguments given!Expected 1 , got (%d).",argc-1);
	}
	int fd = open(argv[1],O_RDONLY);
	CHECK_ERR(fd,2,"Error while opening file");

	int pfd[2];
	int result;
	result = pipe(pfd);
	CHECK_ERR(result,2,"Error while piping");

	pid_t pid = fork();
	CHECK_ERR(pid,2,"Error while forking");
	//child
	if(pid == 0){
		close(pfd[0]);
		dup2(pfd[1],1);
		dprintf(1,"%s\n","Im here mdfker");
		int curr_res= execlp("cat","cat",argv[1],(char*)NULL);
		CHECK_ERR(curr_res,2,"Error while execing");
	}

	pid = fork();
	if(pid == 0){
		close(pfd[1]);
		dup(pfd[0]);
		dprintf(1,"%s\n","Im here but mb blocked");
		int curr_res = execlp("sort","sort",(char *) NULL);
		CHECK_ERR(curr_res,2,"Error while execing");

	}
	dprintf(1,"%s\n","Before closing write end");
	close(pfd[1]);
	dprintf(1,"%s\n","Parent closed write end");
	close(pfd[0]);
	dprintf(1,"%s\n","Parent terminated successfully");
	exit(0);




}
