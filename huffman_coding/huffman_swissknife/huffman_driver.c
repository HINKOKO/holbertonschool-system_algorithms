#include "../huffman.h"
#include "../heap/heap.h"

int main(int argc, char *argv[])
{
	int ret = 0;

	if (argc != 4 || *argv[1] != 'c' || *argv[1] != 'd')
	{
		fprintf(stderr, "Usage: huffman <mode> <filename> <out_filename>\n");
		return (EXIT_FAILURE);
	}
	ret = check_access(argc, argv);
}
