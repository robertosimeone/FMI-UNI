#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>	
#define CHECK_ERR(result,err_code,message)if(result == -1){err(err_code,message);}

static void myread(int fd,char * cmd,int start){
	int read_bytes;
	char symbol;
	int cnt = start;
	while( (read_bytes = read(fd,&symbol,sizeof(symbol))) == sizeof(symbol)){
			if(symbol == '\n'){
				break;
			}else{
				cmd[cnt] = symbol;
				cnt++;
			}
	
	}
	CHECK_ERR(read_bytes,2,"Error while reading");
	cmd[cnt] = '\0';
}
int main(int argc,char ** argv){
	
	if(argc!=1){
		errx(1,"Expected 0 argument,got (%d) instead",argc-1);
	}
	int status;
	char cmd[200] = "/bin/";
	while(true){
		write(1,"> ",2);
		myread(0,cmd,5);
		if(strcmp("/bin/exit",cmd)==0){
			break;
		}
		pid_t pid = fork();
		CHECK_ERR(pid,2,"Could not fork");
		//child
		if(pid == 0){
			execl(cmd,cmd,(char*)NULL);
		}
		int res = wait(&status);
		CHECK_ERR(res,2,"Could not wait");
		if(!WIFEXITED(status)){
			errx(10,"Child process did not terminate normally");
		}
		if(WEXITSTATUS(status)!=0){
			errx(11,"Child process finished with exit status not 0");
		}
		
	
	}
	exit(0);
}
