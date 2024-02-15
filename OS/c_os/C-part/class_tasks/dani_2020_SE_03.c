#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <sys/wait.h>

struct __attribute__((packed)) triplet
{
	const char name[8];
	uint32_t offset;
	uint32_t length;
};

static void sys_error_check(int return_val,int err_num,char* err_msg)
{
	if(return_val == -1)
	{
		err(err_num,err_msg);
	}
}

static void check_file_name(const char *file_name)
{
	if(file_name[7] == 0)
	{
		errx(5,"Wrong file name!");
	}
}

void child_process(int fd,uint32_t offset,uint32_t length,int pipe_out)
{
	sys_error_check(lseek(fd,offset,SEEK_SET),6,"Couldnt apply offset!");
	
	uint16_t result = 0;

	for(uint32_t i = 0; i < length; i++)
	{
		uint16_t current_element = 0;
		sys_error_check(read(fd,&current_element,sizeof(current_element)),7,"Coudlnt read from file!");
		
		result ^= current_element;
	}
	
	sys_error_check(write(pipe_out,&result,sizeof(result)),8,"Couldnt write to file!");

}

	
int main(uint8_t argc,char **argv)
{
	if(argc != 2)
	{
		errx(1,"Wrong arg count!");
	}

	int pipds[2];

	sys_error_check(pipe(pipds),3,"Couldnt init pipe!");
	
	int main_fd = open(argv[1],O_RDONLY);

	sys_error_check(main_fd,4,"Couldnt open main file!");

	for(uint8_t i = 0; i < 8; i++)
	{	
		struct triplet t;
		sys_error_check(read(main_fd,&t,sizeof(t)));

		if(current_file[0] == 0)
		{
			break;
		}

		check_file_name(t.name);

		
		pid_t pid = fork();

		if(pid == 0)
		{
			close(pipds[0]);
			int fd = open(t.name,O_RDONLY);

			sys_error_check(fd,9,"Coudlnt open file!");

			child_process(fd,t.offset,t.length,pipds[1]);
	
			close(fd);	
			exit(0);
		}
	}

	close(pipds[1]);
	
	uint16_t result = 0;
	uint16_t current = 0;
	int bytes_read = 0;

	while(bytes_read = read(pipds[0],&current,sizeof(current)))
	{	
		sys_error_check(bytes_read,9,"Coudlnt read from file!");

		result ^= current;
	}

	dprintf(1,"result: %x",result);


	return 0;
}
	
