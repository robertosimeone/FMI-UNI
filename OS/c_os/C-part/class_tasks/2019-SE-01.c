#include <err.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

uint8_t counter = 0;
uint8_t TH = 0;

static bool cond(time_t endTime, time_t startTime, int exitCode)
{
	if(exitCode != 0 && endTime - startTime < TH)
	{
		if(counter == 1)
		{
			return true;
		}

		counter += 1;
		return false;
	}

	counter = 0;
	return false;
}

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		errx(1, "At least 3 arguments exptected. Usage: ./main <seconds> <program> [args..]");
	}

	int logFd = open("run.log", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	if(logFd == -1)
	{
		err(4, "Could not open log file");
	}

	TH = atoi(argv[1]);

	time_t endTime = 0;
	time_t startTime = 0;
	int exitCode = 0;

	do {
		startTime = time(NULL);
		// Call Q
		pid_t pid = fork();
		if(pid == -1)
		{
			err(2, "Could not fork");
		}

		if(pid == 0)
		{
			if(execvp(argv[2], argv + 2) == -1)
			{
				err(3, "Could not exec");
			}
		}

		int status;
		wait(&status);

		endTime = time(NULL);

		if(WIFEXITED(status))
		{
			exitCode = WEXITSTATUS(status);
		}
		else
		{
			exitCode = 129;
		}

		dprintf(logFd, "%ld %ld %d\n", startTime, endTime, exitCode);
	} while(!cond(endTime, startTime, exitCode));

}
