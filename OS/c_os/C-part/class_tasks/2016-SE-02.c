#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <err.h>
#include <assert.h>
#include <sys/wait.h>

int main(void)
{

	char buffer[256] = "/bin/";
	int i = 5;

	while(1)
	{
		if(write(1, "> ", 2) == -1)
		{
			err(1, "Could not write to stdout");		
		}
		char symbol;
		while(1)
		{
			if(read(0, &symbol, sizeof(symbol)) == -1)
			{
				err(2, "Could not read");
			}

			if(symbol == '\n')
				break;
			else
			{
				buffer[i] = symbol;
				i++;
				assert(i < 255);
			}
		}
		buffer[i] = '\0';
		i = 5;

		if(strcmp(buffer, "/bin/exit") == 0)
		{
			break;
		}

		const pid_t pid = fork();
		if(pid == -1)
		{
			err(4, "Could not fork");
		}
		if(pid == 0)
		{
			if(execl(buffer, buffer, NULL) == -1)
			{
				err(3, "Could not exec");
			}
		}

		int status;
		wait(&status);
		if(!WIFEXITED(status))
		{
			errx(4, "Err");
		}
	}

	return 0;
}
