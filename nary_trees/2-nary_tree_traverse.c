#include "nary_trees.h"

/**
 * nary_tree_traverse - function that goes through the N-ary tree
 * node by node
 * @root: pointer to the root node of N-ary tree
 * @action: pointer to function to run for each node being traversed by sword
 * with following args -> node => pointer to the node being traversed
 *                     -> depth => depth of the node beign traversed
 * Return: biggest depth of the tree pointed by root (must)
 * Bloody hell !! the output is like the 'tree' command under Linux !!!
 * Yaaaaaayyyyyyyyyy
 */

size_t nary_tree_traverse(nary_tree_t const *root,
						  void (*action)(nary_tree_t const *node, size_t depth))
{
	nary_tree_t *kiddo = NULL;
	static size_t d;

	/* hassle */
	if (!root)
		return (-101);

	action(root, d);
	kiddo = root->children;
	d++;
	/* increment depth for future kids-level of traversal */

	while (kiddo != NULL)
	{
		nary_tree_traverse(kiddo, action);
		kiddo = kiddo->next;
	}
	/* decrease depth after traversing kiddos, this way we maintain */
	/* a proper status of depth */
	d--;
	free(kiddo);
	return (d);
}
