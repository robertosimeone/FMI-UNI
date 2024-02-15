#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>


#define CHECK_ERR(result,err_code,message) if (result == -1){err(err_code,message);}

int main(int argc,char ** argv){

	if(argc!=3){
		errx(1,"Wrong number of arguments,expected 2 , got (%d) instead.",argc-1);
	}
	
	int ofd = open(argv[2],O_TRUNC|O_CREAT | O_WRONLY,0644);
	CHECK_ERR(ofd,2,"Error while opening");

	int pfd[2];
	int result = pipe(pfd);
	CHECK_ERR(result,2,"Error while piping");
	
	pid_t pid = fork();
	CHECK_ERR(pid,2,"error while forking");
	//child process
	if(pid == 0){
		close(pfd[0]);
		int dres = dup2(pfd[1],1);
		CHECK_ERR(dres,2,"Error while duping");
		int exresult = execlp("/bin/cat","cat",argv[1],(char *) NULL);
		CHECK_ERR(exresult,2,"Error while execing");
	}
	
	//father  continues
	int status;
	wait(&status);
	if(!WIFEXITED(status)){
		err(3,"Child did not terminate normally");
		}
	if(WEXITSTATUS(status) != 0){
		err(4,"Child did not terminate with exit code 0");
	}
	close(pfd[1]);
	int read_bytes;
	uint8_t byte;
	uint8_t special = 0x20;
	
	while( (read_bytes = read(pfd[0],&byte,sizeof(byte))) == sizeof(byte)){
				if(byte == 0x7D){
					int cread_bytes = read(pfd[0],&byte,sizeof(byte));
					CHECK_ERR(cread_bytes,2,"Error while reading");
					uint8_t result_byte = byte ^ special;
					int written_bytes = write(ofd,&result_byte,sizeof(result_byte));
					CHECK_ERR(written_bytes,2,"Error while writing");
				}
				else{
					int written_bytes = write(ofd,&byte,sizeof(byte));
					CHECK_ERR(written_bytes,2,"Error while writing");
				}
		
	}
	dprintf(1,"Finished reading mdfker, and read bytes is [ %d ]",read_bytes);
	CHECK_ERR(read_bytes,2,"err while reading");
	

}
