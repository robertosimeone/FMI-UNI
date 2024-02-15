#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <err.h>
#include <time.h>
#include <sys/wait.h> 
#define CHECK_ERR(result,err_code,message) if(result == -1){err(err_code,message);}
int count = 0;
int main(int argc,char **argv){
	int e_status;
	uint8_t threshold = atoi(argv[1]);
	char * program = argv[2];
 	char * args[argc-1];
 	for(int i =0 ; i < argc-2;i++){
		args[i] = argv[i+2];

 	}
 	args[argc-2] = (char*)NULL;
 	while(true){
	pid_t pid = fork();
	CHECK_ERR(pid,2,"Error while forking");
	time_t start_time = time(NULL);
	if(pid == 0){
		int exr = execvp(program,args);
		CHECK_ERR(exr,2,"Error while execing");
	}
	else{
		int status;
		int w = wait(&status);
		CHECK_ERR(w,2,"Error while waiting");

		if(!WIFEXITED(status)){	
			err(2,"The child did not terminate properly");
		}
		e_status = WEXITSTATUS(status);
		time_t end_time = time(NULL);
		time_t duration = start_time-end_time;
		if(e_status && duration <threshold){
					count++;
					if(count==2){
							break;
					}

		}
		else{
			count = 0;
			
		}	
	}

	}


}
