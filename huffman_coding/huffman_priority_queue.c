#include "huffman.h"
#include "heap/heap.h"

/**
 * compare - comparison function
 * ==> when we created 'heap_create()' with 'int (*data_cmp) as a parameter'
 * -> it's a pointer to comparison function, taking 2 voids params,
 * returning difference between data in nodes, so that we can build our heap.
 *
 * here we have to compare the frequencies in order to build the priority queue
 *
 * @fr1: frequence in one node
 * @fr2: frequence in following node
 * Return: difference between fr1 && fr2
 *
 */

int compare(void *fr1, void *fr2)
{
	/* freq ==> in symbol_t */
	return (((symbol_t *)((binary_tree_node_t *)fr1)->data)->freq -
			((symbol_t *)((binary_tree_node_t *)fr2)->data)->freq);
}
/**
 * huffman_priority_queue - creates priority queue for Huffman coding
 * @data: array of chars of size size
 * @freq: array of associated frequencies
 * @size: size of arrays
 *
 * Return: pointer to created min heap (priority queue)
 */

heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *huff_heap = NULL;
	binary_tree_node_t *nested = NULL, *node = NULL;
	symbol_t *herz = NULL;
	size_t i;

	huff_heap = heap_create(compare);
	if (!huff_heap)
		return (NULL);

	for (i = 0; i < size; ++i)
	{
		/* create the symbols */
		herz = symbol_create(data[i], freq[i]);
		/* create the nodes */
		nested = binary_tree_node(NULL, herz);
		/* insert them in min heap */
		node = heap_insert(huff_heap, nested);
	}
	return (huff_heap);
}
