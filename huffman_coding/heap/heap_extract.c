#include "heap.h"

/**
 * convert - converts a heapsize to its bit string map
 * @heapsize: size of the heap to build the string map of
 * @base: binary base for us
 * Return: pointer to beginning of the string
 */

char *convert(size_t heapsize, size_t base)
{
	char *TOKENS = "01", *ptr = NULL;
	static char buff[64];

	ptr = &buff[sizeof(buff)];
	*--ptr = 0;
	do
	{
		*--ptr = TOKENS[(heapsize % base)];
		heapsize /= base;
	} while (heapsize);
	return (ptr);
}

/**
 * heapify_down - restores the heap by sinking it down
 * after finding the last level order node in heap_extract()
 * @heap: pointer to heap to fix property of
 */

void heapify_down(heap_t *heap)
{
	binary_tree_node_t *child = NULL, *node = heap->root;
	void *tmp;

	while (1)
	{
		/* true ? its over then Complete BT fullfilled*/
		if (!node->left)
			break;
		if (!node->right)
			child = node->left;
		else
			child = (heap->data_cmp(node->left->data, node->right->data) < 0
						 ? node->left
						 : node->right);
		if (heap->data_cmp(node->data, child->data) < 0)
			break;
		tmp = node->data;
		node->data = child->data;
		child->data = tmp;
		/* make the while roll */
		node = child;
	}
}

/**
 * heap_extract - extract the root node of Min heap
 * @heap: pointer to the heap from which to extract value
 * Return: pointer to the value extracted
 */

void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *node = NULL;
	void *data = NULL;
	char *bitstr = NULL;
	size_t i = 1;

	if (!heap || !heap->root)
		return (NULL);
	data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size--;
		return (data);
	}
	bitstr = convert(heap->size, 2);

	/* boom ! find the last level order node */

	for (node = heap->root; i < strlen(bitstr); i++)
		node = bitstr[i] == '1' ? node->right : node->left;

	/* throw that data of this node to be the new root */
	heap->root->data = node->data;
	/* free this place */
	if (node->parent->left == node)
		node->parent->left = NULL;
	else
		node->parent->right = NULL;

	/* liberate the last level order found */
	free(node);
	--(heap->size);
	/* fix the mess */
	heapify_down(heap);
	return (data);
}
