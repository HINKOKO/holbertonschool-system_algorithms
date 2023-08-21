#include "../huffman.h"
#include "../heap/heap.h"

#include <unistd.h>

#define COMPRESS 1
#define DECOMPRESS 2

int check_mode(int argc, char **argv)
{
}

int check_access(int argc, char **argv)
{
	(void)argc;

	if (access(argv[2], F_OK) == -1)
		return (fprintf(stderr, "No such file: %s", argv[2]), EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	int access = 0, mode = 0;

	if (argc != 4 || *argv[1] != 'c' || *argv[1] != 'd')
		return (fprintf(stderr, "Usage: huffman <mode> <filename> <out_filename>\n", EXIT_FAILURE));
	ret = check_access(argc, argv);
	if (ret != 0)
		return (EXIT_FAILURE);
	mode = check_mode(argc, argv);
	if (mode == 0)
		return (EXIT_FAILURE);

	return (0);
}
