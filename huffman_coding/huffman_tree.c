#include "huffman.h"

/**
 * huffman_tree - Builds the Huff-tree
 * @data: array of chars of size size
 * @freq: array of associated frequencies
 * @size: size of arrays
 *
 * Return: pointer to the root node of Huff-tree, NULL if failure
 */

binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *huff_root = NULL;
	heap_t *huff_queue = huffman_priority_queue(data, freq, size);

	if (!huff_queue)
		return (NULL);

	while (huff_queue->size > 1)
		huffman_extract_and_insert(huff_queue);

	huff_root = huff_queue->root->data;
	heap_delete(huff_queue, NULL);
	return (huff_root);
}
