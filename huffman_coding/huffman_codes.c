#include "huffman.h"

/**
 * print_codes - go down the tree starting at root
 * append a '0' when goind to left, append a '1'
 * if going to right
 * @root: root node of Huffman tree
 * @pathlocation: the path as an 'int', that we can convert to binary code
 * using the convert() function from heap_extract
 */

void print_codes(binary_tree_node_t *root, size_t pathlocation)
{
	symbol_t *symbol = NULL;

	symbol = root->data;
	/* we reached a leaf */
	if (symbol->data != '$')
		printf("%c: %s\n", symbol->data, convert(pathlocation, 2) + 1);
	else
	/* recursive call to go down the tree */
	{
		/* child nodes 'i' on left are at 2i */
		print_codes(root->left, pathlocation * 2);
		/* child nodes 'i' on right are at 2i + 1 */
		print_codes(root->right, (pathlocation * 2) + 1);
	}
	free(symbol);
	free(root);
}

/**
 * huffman_codes - build huffman tree and print resulting
 * Huffman codes, highlight of the show!
 * @data: array of chars of size size
 * @freq: array of associated frequencies
 * @size: size of arrays
 *
 * Return: 1 for success, 0 on failure
 */

int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root = huffman_tree(data, freq, size);

	if (!root)
		return (0);
	print_codes(root, 1);
	return (1);
}
