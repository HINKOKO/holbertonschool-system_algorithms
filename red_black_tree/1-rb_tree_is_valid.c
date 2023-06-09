#include "rb_trees.h"
/**
 * check_rb_tree - check if rb tree is the one it
 * pretends to be!
 * @node: pointer to current node
 * Return: 1 for valid RBT, 0 otherwise
 */

int check_rb_tree(const rb_tree_t *node)
{
	if (!node->right || !node->left)
		return (1);
	if (!node->color)
		return (0);
	if (node->color == RED)
	{
		if (node->parent->color == node->color)
			return (0);
		if (node->color == node->left->color || node->color == node->right->color)
			return (0);
	}
	return (check_rb_tree(node->right) && check_rb_tree(node->left));
}

/**
 * rb_tree_is_valid - checks if a binary tree is valid RBT
 * @tree: pointer to root node of supposed RBT
 * => check is color first -> has to be BLACK
 * Return: 1 for valid RBT, 0 otherwise
 */

int rb_tree_is_valid(const rb_tree_t *tree)
{
	if (!tree)
		return (0);
	if (tree->color != BLACK)
		return (0);
	return (check_rb_tree(tree->left) && check_rb_tree(tree->right));
}
