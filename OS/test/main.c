#include <fcntl.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char * argv[]){

	write(1,argv[0],strlen(argv[0]));
	write(1,argv[1],strlen(argv[1]));
	exit(0);
}
