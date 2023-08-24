#include "../huffman.h"
#include "../heap/heap.h"

#include <unistd.h>

#define COMPRESS 1
#define DECOMPRESS 2

/* int access(const char *pathname, int mode); */
/* F_OK mode check for existence of the file */

int main(int argc, char **argv)
{
	int ret = EXIT_FAILURE;

	if (argc != 4)
		return (fprintf(stderr, "Usage: huffman <mode> <filename> <out_filename>\n"), EXIT_FAILURE);

	if (access(argv[2], F_OK) == -1)
		return (fprintf(stderr, "No such file: %s\n", argv[2]), EXIT_FAILURE);

	if (access(argv[3], F_OK) != -1)
		return (fprintf(stderr, "File already exists: %s\n", argv[3]), EXIT_FAILURE);

	if (!strcmp(argv[1], "c"))
		printf("Compression mode detected, please wait...\n");
	else if (!strcmp(argv[1], "d"))
		printf("Decompression mode detected, please wait...\n");
	else
		printf("Mode usage: either \"c\" for compression, or \"d\" for decompression.Take care\n");

	return (ret);
}
