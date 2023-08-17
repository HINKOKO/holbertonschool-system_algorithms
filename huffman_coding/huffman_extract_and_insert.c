#include "huffman.h"
#include "heap/heap.h"

/**
 * huffman_extract_and_insert - extract two nodes of priority
 * queue and insert new one containing freq1 + freq2
 * @priority_queue: pointer to the prior queue to extract/insert
 * Return: 1 on Success, 0 on failure
 *
 */

int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *nest1 = NULL, *nest2 = NULL;
	binary_tree_node_t *node = NULL, *pushback = NULL;
	size_t freq = 0;
	symbol_t *new_symbol = NULL;

	if (!priority_queue)
		return (0);

	/* pop the two least significant from min heap */
	nest1 = heap_extract(priority_queue);
	nest2 = heap_extract(priority_queue);

	freq = ((symbol_t *)(nest1->data))->freq +
		   ((symbol_t *)(nest2->data))->freq;
	new_symbol = symbol_create('$', freq);
	node = binary_tree_node(NULL, new_symbol);
	pushback = heap_insert(priority_queue, node);
	if (!pushback)
		return (0);
	--(priority_queue->size);
	return (1);
}
