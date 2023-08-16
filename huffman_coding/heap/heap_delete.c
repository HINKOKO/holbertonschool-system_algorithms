#include "heap.h"

/**
 * freedom - recursively free the entire heap
 * @node: pointer to root of heap/BT
 * @free_data: pointer to a function used to free (NULL at first)
 */

void freedom(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;
	freedom(node->left, free_data);
	freedom(node->right, free_data);
	/* used with NULL in the 4-main.c */
	if (free_data == NULL)
		free(node);

	else
		free(node), free(node->data);
}
/**
 * heap_delete - deallocates a heap
 * @heap: pointer to the heap to free's
 * @free_data: pointer to function
 *
 */

void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;
	/* start at heap->root */
	freedom(heap->root, free_data);
	free(heap);
}
