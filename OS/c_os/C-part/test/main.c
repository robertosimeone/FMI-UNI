#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
int main(void){
	uint32_t n = 522;
	int fd = open("robi.txt",O_CREAT | O_TRUNC | O_WRONLY,0666);
	write(fd,&n,sizeof(uint16_t));

}
