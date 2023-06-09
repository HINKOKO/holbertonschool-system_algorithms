#include "rb_trees.h"

/**
 * rb_tree_verify - helper function to verify if RBTree
 * is the one it pretends to be
 * @node: pointer to root node
 * @black_n: number of black node
 * @path_count: number of black nodes along given path
 * Return: 1 if valid, 0 otherwise
 */

int rb_tree_verify(const rb_tree_t *node, int black_n, int path_count)
{
	if (node == NULL)
		return (1);

	/* property 4 => if a root is red, both children should be black */
	if (node->color == RED)
	{
		if (node->left != NULL && node->left->color != BLACK)
			return (0);
		if (node->right != NULL && node->right->color != BLACK)
			return (0);
	}

	/* count black nodes (recursion will count)*/
	if (node->color == BLACK)
		black_n++;

	/* property 5 verification */
	if (node->left == NULL && node->right == NULL)
	{
		if (path_count == -1)
			path_count = black_n;
		else if (path_count != black_n)
			return (0);
	}
	return (rb_tree_verify(node->left, black_n, path_count) &&
			rb_tree_verify(node->right, black_n, path_count));
}

/**
 * rb_tree_is_valid - checks if a binary tree is valid RBT
 * @tree: pointer to root node of supposed RBT
 * => check is color first -> has to be BLACK
 * Return: 1 for valid RBT, 0 otherwise
 */

int rb_tree_is_valid(const rb_tree_t *tree)
{
	int black_nodes = 0, b_along_path = -1;
	int res = 0;

	if (tree == NULL)
		return (1);
	if (tree->color != BLACK)
		return (0);
	res = rb_tree_verify(tree, black_nodes, b_along_path);
	return (res);
}
