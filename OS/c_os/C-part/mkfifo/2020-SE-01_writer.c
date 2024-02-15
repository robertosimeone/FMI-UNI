#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>


int main(int argc, char** argv)
{
	if(argc != 2)
	{
		errx(2, "Expected a file");
	}

	if(mkfifo("myfifo", S_IRWXU) == -1)
	{
		err(1, "Could not make fifo");
	}

	int fd = open("myfifo", O_WRONLY);
	if(fd == -1)
	{
		err(2, "Could not open fifo");
	}

	close(1);
	if(dup(fd) == -1)
	{
		err(5, "Dup failed");
	}
	if(execlp("cat", "cat", argv[1], NULL) == -1)
	{
		err(6, "Exec failed");
	}
	return 0;
}
