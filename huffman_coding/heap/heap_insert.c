#include "heap.h"

/**
 * heapify_up - fix the heap property after insertion
 * @data_cmp: pointer to comparison function (in 2-main)
 * @node: the node to compare to its parent (the one we inserted)
 * Return: pointer to inserted & fixed position node
 */

binary_tree_node_t *heapify_up(int (*data_cmp)(void *, void *),
							   binary_tree_node_t *node)
{
	void *tmp;

	if (!data_cmp || !node)
		return (NULL);
	while (node->parent && data_cmp(node->data, node->parent->data) < 0)
	{
		tmp = node->data;
		node->data = node->parent->data;
		node->parent->data = tmp;

		node = node->parent;
	}
	return (node);
}

/**
 * ith_node - find the proper next available position
 * in the heap , first step to keep the BT Complete BT,
 * then fixed by heapify_up
 * @root: pointer to root node of heap
 * @i: size of the heap
 * Return: location of inserted node
 */

binary_tree_node_t *ith_node(binary_tree_node_t *root, const size_t i)
{
	size_t b = i;

	if (!root || i < 1)
		return (NULL);

	if (i == 1)
		return (root);

	/* find the binary logarithm closest to size*/
	while (b & (b - 1))
		b &= (b - 1);

	/* ignore highest binary digit */
	b >>= 1;

	/* walk down the tree as directed by b roadmap*/
	while (b)
	{
		if (i & b)
			if (root->right)
				root = root->right;
			else
				break;
		else
		{
			if (root->left)
				root = root->left;
			else
				break;
		}
		b >>= 1;
	}
	return (root);
}

/**
 * heap_insert - inserts a value in a Min heap
 * @heap: Pointer to the heap in which to insert
 * @data: POinter containing the data to store in the new node
 * Return: Pointer to the created node, or NULL on failure
 */

binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new = NULL;

	if (!heap || !data)
		return (NULL);

	if (!heap->root)
	{
		heap->root = new = binary_tree_node(NULL, data);
		if (!new)
			return (NULL);
		heap->size++;
	}
	else
	{
		new = ith_node(heap->root, ++heap->size);
		if (!new->left)
			new = new->left = binary_tree_node(new, data);
		else
			new = new->right = binary_tree_node(new, data);
	}

	return (heapify_up(heap->data_cmp, new));
}
