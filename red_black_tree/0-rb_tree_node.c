#include "rb_trees.h"

/**
 * rb_tree_node - creates a Red-Black tree node
 * @parent: pointer to parent node to create
 * @value: value to put in the node
 * @color: color of the node RED || BLACK
 * Return: pointer to the new node or NULL if failure
 */

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new_rb_tree = NULL;

	new_rb_tree = malloc(sizeof(rb_tree_t));
	if (!new_rb_tree)
		return (NULL);
	new_rb_tree->parent = parent;
	new_rb_tree->left = NULL;
	new_rb_tree->right = NULL;
	new_rb_tree->n = value;
	new_rb_tree->color = color;
	return (new_rb_tree);
}
