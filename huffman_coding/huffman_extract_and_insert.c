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
	binary_tree_node_t *node, *extract1, *extract2;
	symbol_t *new;
	size_t sum = 0;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	extract1 = heap_extract(priority_queue);
	extract2 = heap_extract(priority_queue);

	sum = ((symbol_t *)extract1->data)->freq;
	sum += ((symbol_t *)extract2->data)->freq;

	new = symbol_create('$', sum);
	if (!new)
		return (0);
	extract1->parent = extract2->parent = node = binary_tree_node(NULL, new);
	if (!node)
	{
		free(new);
		return (0);
	}
	node->left = extract1;
	node->right = extract2;
	return (heap_insert(priority_queue, node) != NULL);
}
