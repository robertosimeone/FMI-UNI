#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <sys/stat.h>
#include <stdlib.h>

static int compar(const void* a, const void* b)
{
	const uint32_t* av = (const uint32_t*) a;
	const uint32_t* bv = (const uint32_t*) b;
	
	return av - bv;
}
//spored men tuk trqbva da e *av-*bv

void write_to_file(int fd, uint8_t* buffer, int size)
{
	// Or easier... write(fd, buffer, size);
	for(int i = 0; i < size; i++)
	{
		if(write(fd, buffer + i, 1) == -1)
		{
			err(5, "Could not write to output file");
		}
	}
}

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		errx(1, "Arg count");
	}

	int input_fd = open(argv[1], O_RDONLY);
	if(input_fd == -1)
	{
		err(2, "Could not open input file");
	}
	int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR);
	if(input_fd == -1)
	{
		err(3, "Could not open output file");
	}

	struct stat s;
	if(fstat(input_fd, &s) == -1)
	{
		err(3, "Could not stat input file");
	}

	if(s.st_size % 4 != 0)
	{
		errx(4, "Input file should contain only uint32_t's");
	}

	if(s.st_size <= 8388608)
	{
		// Nice part
		uint32_t* buffer = (uint32_t*)malloc(s.st_size);
	
		if(read(input_fd, buffer, s.st_size) == -1)
		{
			err(5, "Could not read input file");
		}
		qsort(buffer, s.st_size / sizeof(uint32_t), sizeof(uint32_t), compar);
		write_to_file(output_fd, (uint8_t*)buffer, s.st_size);

		free(buffer);
	}
	else
	{
		// Bad part
		int tmpf1 = open("tmp1", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR);
		int tmpf2 = open("tmp2", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR);

		uint32_t* buffer = (uint32_t*)malloc((s.st_size / 2)+2);
		if(s.st_size % 8 == 0)
		{
			read(input_fd, buffer, s.st_size / 2);
			write_to_file(tmpf1, buffer, s.st_size / 2);

			read(input_fd, buffer, s.st_size / 2);
			write_to_file(tmpf2, buffer, s.st_size / 2);
		}
		else 
		{
			read(input_fd, buffer, s.st_size / 2 + 2);
			qsort(buffer, s.st_size / sizeof(uint32_t) / 2 + 1, sizeof(uint32_t), compar);
			write_to_file(tmpf1, buffer, s.st_size / 2 + 2);

			read(input_fd, buffer, s.st_size / 2 - 2);
			qsort(buffer, s.st_size / sizeof(uint32_t) / 2 -1, sizeof(uint32_t), compar);
			write_to_file(tmpf2, buffer, s.st_size / 2 - 2);
		}

		free(buffer);

		uint32_t left_elem;
		uint32_t right_elem;
		read(tmpf1, &left_elem, sizeof(left_elem));
		read(tmpf2, &right_elem, sizeof(right_elem));

		u8 to_write = 0;

		while(1)
		{
			if(left_elem < right_elem)
			{
				write(output_fd, &left_elem, sizeof(left_elem));	
				if(read(tmpf1, &left_elem, sizeof(left_elem)) == 0)
				{
					to_write = 2;
					break;
				}
			}
			else
			{
				write(output_fd, &right_elem, sizeof(left_elem));	
				if(read(tmpf2, &right_elem, sizeof(right_elem)) == 0)
				{
					to_write = 1;
					break;
				}
			}
		}

		if(to_write == 1)
		{
			while(read(tmpf1, &left_elem, sizeof(left_elem)))
			{
				write(output_fd, &left_elem, sizeof(left_elem));
			}
		}
		else
		{
			while(read(tmpf2, &right_elem, sizeof(right_elem)))
			{
				write(output_fd, &right_elem, sizeof(right_elem));
			}

		}
	}

}
