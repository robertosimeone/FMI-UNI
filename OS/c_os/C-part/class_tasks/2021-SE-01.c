#include <stdint.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>

static uint16_t manch_encode(uint8_t byte)
{
	uint8_t MASK = 128;
	uint16_t result = 0;
	uint16_t ONE_MASK = 2;
	uint16_t ZERO_MASK = 1;

	for(int i = 0; i < 8; i++)
	{
		if((byte & (MASK >> i))	== 0)
		{
			// Bit was zero
			result = (result << 2) | ZERO_MASK;
		}
		else
		{
			// Bit was one
			result = (result << 2) | ONE_MASK;
		}

	}

	return result;
}

int main(int argc, char** argv)
{

	if(argc != 3)
	{
		errx(1, "Wrong arg count. Usage: ./main input.bin output.bin");
	}

	int input_fd = open(argv[1], O_RDONLY);
	if(input_fd == -1)
	{
		err(2, "Could not open input");
	}
	int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if(output_fd == -1)
	{
		err(3, "Could not open output");
	}


	uint8_t byte;
	int rresult;
	while( (rresult = read(input_fd, &byte, sizeof(byte))) == sizeof(byte) )
	{
		uint16_t result = manch_encode(byte);
		write(output_fd, &result, sizeof(result));
	}

	if(rresult == -1)
	{
		err(4, "Could not read from input");
	}

	return 0;
}
