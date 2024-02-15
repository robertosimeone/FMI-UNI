#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdio.h>

int main(void){
uint8_t byte = 1;
int fd = open("btest",O_TRUNC | O_CREAT | O_WRONLY,0644);
write(fd,&byte,sizeof(byte));

}
