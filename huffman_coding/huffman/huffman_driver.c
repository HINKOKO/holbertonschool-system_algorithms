#include "../huffman.h"
#include "../heap/heap.h"

#include <unistd.h>

char_t *count_symbols(const char *inputfile)
{
	char_t *chars_data = NULL;
	FILE *filename;
	size_t i;
	char c = 0;
	int found;

	chars_data = malloc(sizeof(char_t));
	if (!chars_data)
		return (NULL);
	chars_data->data = calloc(127, sizeof(char));
	chars_data->freq = calloc(127, sizeof(size_t));
	chars_data->size = 0;

	filename = fopen(inputfile, "r");
	while ((c = fgetc(filename)) != EOF && c <= 127)
	{
		found = 0;
		for (i = 0; i < chars_data->size; i++)
		{
			if (c == chars_data->data[i])
				chars_data->freq[i]++, found = 1;
		}
		if (!found)
		{
			chars_data->size++;
			chars_data->data[chars_data->size - 1] = c;
			chars_data->freq[chars_data->size - 1] = 1;
		}
	}
	return (chars_data);
}

int compress(const char *input_file, const char *output_file)
{
	int ret = EXIT_SUCCESS;
	// unsigned char buff[BUFSIZ];
	// binary_tree_node_t *root = NULL;
	char_t *frequencies = NULL;

	frequencies = count_symbols(input_file);

	ret = huffman_codes(frequencies->data, frequencies->freq, frequencies->size);
	if (ret)
		printf("I'm done!");

	return (0);
}

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
		ret = compress(argv[2], argv[3]);

	else if (!strcmp(argv[1], "d"))
		printf("Decompression mode detected, please wait...\n");

	else
		printf("Mode usage: either \"c\" for compression, or \"d\" for decompression.Take care\n");

	return (ret);
}
