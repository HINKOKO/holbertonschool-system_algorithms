#include "heap.h"

/**
 * convert - build the "01" representation of heapsize
 * bit_string in reverse to have it directly in correct-order
 * @heapsize: the heap_size to convert
 * @base: the base to convert to (binary only available here in TOKENS)
 * Return: pointer to begining of bit string repr of heap->size
*/

char *convert(long heapsize, long base)
{
	char *TOKENS = "01", *ptr = NULL;
	static char buffer[64];
	ptr = &buffer[sizeof(buffer)];
	*--ptr = 0;

	do {
		*--ptr = TOKENS[(heapsize % base)];
		heapsize /= base;
	} while (heapsize);
	
	return (ptr);
}


/**
 * heap_insert - inserts a value in a Min heap
 * @heap: Pointer to the heap in which to insert
 * @data: POinter containing the data to store in the new node
 * Return: Pointer to the created node, or NULL on failure
 */

binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	size_t i = 0;
	binary_tree_node_t *new = NULL, *node = NULL;
	void *tmp;
	char *bitstr = NULL;

	if (!heap)
		return (NULL);

	new = binary_tree_node(NULL, data);
	if (!new)
		return (NULL);
	/* increment here */
	heap->size++;
	bitstr = convert(heap->size, 2);

	if (!heap->root)
		return (heap->root = new);
	for (node = heap->root, i = 1; i < strlen(bitstr) - 1; i++)
		node = bitstr[i] == '1' ? node->right : node->left;
	if (bitstr[i] == '1')
		node->right = new;
	else
		node->left = new;
	new->parent = node;
	node = new;
	while (node->parent && heap->data_cmp(node->parent->data, node->data) > 0)
	{
		tmp = node->parent->data;
		node->parent->data = node->data;
		node->data = tmp;
		/* roll up */
		node = node->parent;
	}
	return (new);
}
