#include <stdint.h>
#include <fcntl.h>
#include <stdbool.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#define CHECK_ERR(result,err_code,message) if(result == -1){err(err_code,message);}

int counter = 0;
int pipes[4][2];

static void wait_child(void){
	int status;
	int res = wait(&status);
	CHECK_ERR(res,2,"Couldnt wait");

	if(!WIFEXITED(status)){
		errx(3,"Child did not terminate normally/mb killed : %d",counter);
	}
	if(WEXITSTATUS(status) != 0){
		errx(4,"Child did not finish succ");
	}


}
void arrangePipe(int fd1,int fd2);
void arrangePipe(int fd1,int fd2){
		pipes[counter][0] = fd1;
		pipes[counter][1] = fd2;
		counter++;
}
int main(void){


	//setup pipes;
	int result;
	int curr_pfs[2];
	//child1
	result = pipe(curr_pfs);
	arrangePipe(curr_pfs[0],curr_pfs[1]);
	CHECK_ERR(result,2,"Error while piping");	
	pid_t pid = fork();
	CHECK_ERR(pid,2,"Could not fork");
	if(pid == 0){
			close(pipes[0][0]);
			close(1);
			dup(pipes[0][1]);
			int curr = execlp("cut","cut","-d",":","-f","7","/etc/passwd",(char*)NULL);
			CHECK_ERR(curr,2,"Could not exec");
	}
	wait_child();
	close(pipes[0][1]);
	result = pipe(curr_pfs);
	CHECK_ERR(result,2,"Error while piping");
	arrangePipe(curr_pfs[0],curr_pfs[1]);

	
	pid = fork();
	if(pid == 0){
		dup2(pipes[0][0],0);
		dup2(pipes[1][1],1);
		close(pipes[1][0]);
		int curr = execlp("sort","sort",(char*)NULL);
		CHECK_ERR(curr,2,"Could not exec");
		//mb close all end of pipes here;
	}
	wait_child();
	close(pipes[1][1]);
	result = pipe(curr_pfs);
	CHECK_ERR(result,2,"Error while piping");
	arrangePipe(curr_pfs[0],curr_pfs[1]);



	pid = fork();
	if(pid == 0){
		dup2(pipes[1][0],0);
		dup2(pipes[2][1],1);
		close(pipes[2][0]);
		int curr = execlp("uniq","uniq","-c",(char*)NULL);
		CHECK_ERR(curr,2,"Could not exec");
		//mb close all end of pipes here;
	}
	wait_child();
	close(pipes[2][1]);
	result = pipe(curr_pfs);
	CHECK_ERR(result,2,"Error while piping");
	arrangePipe(curr_pfs[0],curr_pfs[1]);

	
	pid = fork();
	if(pid == 0){
		dup2(pipes[2][0],0);
		close(pipes[3][0]);
		int curr = execlp("sort","-n",(char*)NULL);
		CHECK_ERR(curr,2,"Could not exec");
		//mb close all end of pipes here;
	}
	wait_child();
	dprintf(1,"%s\n","Program finished sucessfully motherfucker!");
	close(pipes[3][1]);

	exit(0);
}
