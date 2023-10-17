#include "nary_trees.h"

/**
 * nary_tree_delete - deallocates an entire N-ary tree
 * @tree: pointer to root node of N-ary tree
 * We go down the tree, accessing first the tree->children then
 * tree->children->next to get the following children for given node and
 * call this by recursion
*/

void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *eraser = NULL;

	if (!tree)
		return (NULL);

	while (tree->children)
	{
		eraser = tree->children;
		tree->children = tree->children->next;
		nary_tree_delete(eraser);
	}
	free(tree->content);
	free(tree);
}
