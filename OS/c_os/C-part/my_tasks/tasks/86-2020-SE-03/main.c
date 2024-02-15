#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define CHECK_ERR(result,err_code,message) if(result==-1){err(err_code,message);}

int main(int argc,char ** argv){

	if(argc!=2){
		errx(1,"Wrong number of arguments given,expected 1, got (%d) instead.",argc-1);
	}
	











}
