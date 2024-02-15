#include <unistd.h>
#include <fcntl.h>
#include <err.h>


int main(int argc, char** argv)
{
	if(argc != 2)
	{
		errx(1, "Arg count");
	}
	int fd = open("myfifo", O_RDONLY);
	if(fd == -1)
	{
		err(2, "open");
	}
	close(0);
	
	if(dup(fd) == -1)
	{
		err(3, "Could not dup");
	}
	if(execl(argv[1], argv[1], NULL) == -1)
	{
		err(4, "Could not exec");
	}
}

