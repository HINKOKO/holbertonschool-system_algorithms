#include "nary_trees.h"

/**
 * path_exists - function to check if a path exists
 * in an N-ary tree
 * @root: pointer to root node of N-ary tree
 * @path: NULL terminated array of strings
 *
 * Return: must return 1 if all elements of path, are present in the tree
 * and if for an element oif path at index 'i' is present
 * in one of the nodes at depth 'i'
 * => For sure, all nodes must be linked to form a path
 * otherwise How to walk the line Mister Cash Johnny ?
 */

int path_exists(nary_tree_t const *root, char const *const *path)
{
	nary_tree_t *curr = (nary_tree_t *)root;

	while (*path != NULL && curr != NULL)
	{
		if (!strcmp(curr->content, *path))
			path++, curr = curr->children;
		else
			curr = curr->next;
	}
	return (*path == NULL);
}
