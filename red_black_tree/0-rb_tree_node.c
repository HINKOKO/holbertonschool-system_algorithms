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

/**
 * rbt_right_rotate - performs right rotation learnt in AVL project
 * @tree: db pointer to root node
 * @node: the node to flip flap
 */

void rbt_right_rotate(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *flip = NULL;

	flip = node->left;
	node->left = flip->right;
	if (flip->right)
		flip->right->parent = node;
	flip->parent = node->parent;
	if (node->parent == NULL)
	{
		/* to rotating reached the top */
		*tree = flip;
	}
	else if (node == node->parent->left)
		node->parent->left = flip;
	else
		node->parent->right = flip;
	flip->right = node;
	node->parent = flip;
}

/**
 * rbt_left_rotate - performs lef trotation learnt in AVL project
 * @tree: db pointer to root node
 * @node: the node to flip flap
 */

void rbt_left_rotate(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *flip = NULL;

	flip = node->right;
	node->right = flip->left;
	if (flip->left)
		flip->left->parent = node;
	flip->parent = node->parent;
	if (node->parent == NULL)
		*tree = flip;
	else if (node == node->parent->left)
		node->parent->left = flip;
	else
		node->parent->right = flip;
	flip->left = node;
	node->parent = flip;
}
