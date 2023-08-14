#include "heap.h"

#define ABS(x) ((x) >= 0 ? (x) : (-x))

char *convert(long num, long base)
{
	char *ptr;
	char *TOKENS = "0123456789ABCDEFG";
	static char buff[66];

	ptr = &buff[sizeof(buff)];
	*--ptr = 0;
	do {
		*--ptr = TOKENS[ABS(num % base)];
		num /= base;
	} while (num);
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
	binary_tree_node_t *new_node, *node;
	void *tmp = NULL;
	size_t i;
	char *_map;

	if (!heap)
		return (NULL);

	new_node = binary_tree_node(NULL, data);
	if (!new_node)
		return (NULL);
	

	if (!heap->root)
		return (heap->root = new_node);

	_map = convert(heap->size, 2);
	for (node = heap->root, i = 1; i < strlen(_map) - 1; i++)
		node = _map[i] == '1' ? node->right : node->left;

	if (_map[i] == '1')
		node->right = new_node;
	else
		node->left = new_node;
	new_node->parent = node;
	node = new_node;
	while (node->parent && heap->data_cmp(node->parent->data, node->data) > 0)
	{
		tmp = node->data;
		node->data = node->parent->data;
		node->parent->data = tmp;
		node = node->parent;
	}
	++(heap->size);
	return (new_node);
}
