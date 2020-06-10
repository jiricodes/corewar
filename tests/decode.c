#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>

int32_t		decode(const uint8_t *source, size_t size)
{
	int32_t result;
	uint8_t sign;
	size_t i;

	if (source[0] & 128)
		sign = 255;
	else
		sign = 0;
	result = 0;
	i = 0;
	while (i < size)
	{
		result += (source[size - (i + 1)] ^ sign) << (i * 8);
		i++;
	}
	if (sign)
		result = ~result;
	return (result);
}

int main(int argc, char **argv)
{
	int fd;
	uint8_t buffer[4];
	size_t	ret;
	int32_t res;

	if (argc != 2)
		exit(0);
	fd = open(argv[1], O_RDONLY);
	if (fd >= 0)
	{
		ret = read(fd, buffer, 4);
		res = decode(buffer, 4);
		printf("%#x\n", res);
	}
	return (0);
}