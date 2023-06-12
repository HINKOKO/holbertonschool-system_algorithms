#include "rb_trees.h"

/**
 * fix_left - perform left rotation for fixing broken RBT
 * @node: pointer to node to fix/rotate
 * @value: the value to fix/rotate
 * @color: color of the node
 * Return: pointer to inserted and fixed position node
 */

rb_tree_t *fix_left(rb_tree_t *node, int value, rb_color_t color)
{
	node->parent->right = rb_tree_node(node->parent, value, color);
	node->parent->right->n = node->parent->n;
	node->parent->n = node->n;
	node->n = value;
	return (node);
}

/**
 * fix_right - perform right rotation for fixing broken RBT
 * @node: pointer to node to fix/rotate
 * @value: the value to fix/rotate
 * @color: color of the node
 * Return: pointer to inserted and fixed position node
 */

rb_tree_t *fix_right(rb_tree_t *node, int value, rb_color_t color)
{
	node->parent->left = rb_tree_node(node->parent, value, color);
	node->parent->left->n = node->parent->n;
	node->parent->n = node->n;
	node->n = value;
	return (node);
}

/**
 * rb_tree_insert - performs insertion in a RBT
 * @tree: double pointer to the root node of RBT
 * @value: value to store in new node inserted
 * Return: pointer to the created node, or NULL if failure
 */

rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *tmp = *tree;
	rb_color_t color;

	if (!(*tree))
		return (*tree = rb_tree_node(NULL, value, BLACK));
	if (tmp->color == RED)
		color = BLACK;
	color = RED;

	if (tmp->n == value)
		return (NULL);
	if (tmp->n > value)
	{
		if (tmp->left == NULL)
		{
			if (tmp->parent)
				if (tmp->parent->n > value && !tmp->parent->right &&
					!tmp->left && !tmp->right)
					return (fix_left(tmp, value, color));
			return (tmp->left = rb_tree_node(tmp, value, color));
		}
		else
			return (rb_tree_insert(&tmp->left, value));
	}
	else
	{
		if (tmp->right == NULL)
		{
			if (tmp->parent)
				if (tmp->parent->n < value && !tmp->parent->left &&
					!tmp->left && !tmp->right)
					return (fix_right(tmp, value, color));
			return (tmp->right = rb_tree_node(tmp, value, color));
		}
		else
			goto out;
	}
out:
	return (rb_tree_insert(&tmp->right, value));
}
