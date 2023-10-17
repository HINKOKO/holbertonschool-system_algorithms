#include "nary_trees.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/**
 * max_height - utility func to return max height of tree
 * @node: pointer to curr node
 * Return: the maxdepth of tree
 */

size_t max_height(nary_tree_t *node)
{
	nary_tree_t *tmp = NULL;
	size_t maxd = 0;
	/* hassle */
	if (!node)
		return (0);

	for (tmp = node->children; tmp; tmp = tmp->next)
		maxd = MAX(maxd, max_height(tmp));

	return (maxd + 1);
}

/**
 * nary_tree_diameter - computes the diameter of an N-ary tree
 * @root: pointer to root node to compute diameter of
 * Return: must -> the diameter boy !
 *
 */

size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t max1 = 0, max2 = 0, h;
	size_t max_child_diam = 0;
	nary_tree_t *kid = NULL;

	for (kid = root->children; kid; kid = kid->next)
	{
		h = max_height(kid);
		if (h > max1)
			max2 = max1, max1 = h;
		else if (h > max2)
			max2 = h;
	}
	for (kid = root->children; kid; kid = kid->next)
		max_child_diam = MAX(max_child_diam, nary_tree_diameter(kid));

	return (MAX(max_child_diam, max1 + max2 + 1));
}
