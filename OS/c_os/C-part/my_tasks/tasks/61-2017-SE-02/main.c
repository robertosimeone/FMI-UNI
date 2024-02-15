#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define CHECK_ERR(result,err_code,message) if(result == -1){err(err_code,message);}
#include <stdbool.h>
#include <string.h>
uint32_t line=1;
static void printFile(int fd,bool line_number){
	if(line_number){	
	dprintf(1,"%d : ",line);
	}
	int bytes_read;
	char symbol;
	while((bytes_read = read(fd,&symbol,sizeof(symbol))) == sizeof(symbol)){
		if(symbol == '\n'){
			int res = read(fd,&symbol,sizeof(symbol));
			if(res == 0){
				line++;
				write(1,"\n",1);
				break;
			}
			else{
			write(1,"\n",1);
			if(line_number){
			line++;
			dprintf(1,"%d : ",line);
			}
			}
		}
		int res = write(1,&symbol,sizeof(symbol));

		if(symbol == '\n' && line_number){
			line++;
			dprintf(1,"%d : ",line);
		}

		CHECK_ERR(res,1,"Error while writing");
	}
	
	if(bytes_read == 0)
		write(1,"\n",1);
	CHECK_ERR(bytes_read,1,"Error while reading");



}
int main(int argc, char ** argv){
		// only stdin
	int start = 1;
	bool flag = false;
	if(argc == 1){
		printFile(0,flag);
		exit(0);
	}
	if(argc == 2 && strcmp(argv[1],"-n") == 0){
		printFile(0,true);
		exit(0);
	}
	if(argc >=2){
		if(strcmp(argv[1],"-n")==0){
		start = 2;
		flag = true;
		}

	for(int i = start;i<argc;i++){
			if(strcmp(argv[i],"-")==0){
				printFile(0,flag);			

			}
			else{
			int fd = open(argv[i],O_RDONLY);
			CHECK_ERR(fd,1,"Error while opening");
			printFile(fd,flag);
			close(fd);
			}
	}
	}



	exit(0);
}
