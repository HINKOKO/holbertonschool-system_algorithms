#include "heap.h"

/**
 * binary_tree_node - creates a generic BinaryTreeNode
 * @parent: Pointer to the parent node of the node to be created
 * @data: data to be stored in the node
 *
 * Return: Pointer to the created node or NULL on failure
 */

binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new;

	new = malloc(sizeof(binary_tree_node_t));
	if (!new)
		return (NULL);

	new->parent = parent;
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	return (new);
}
