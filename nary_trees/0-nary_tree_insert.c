#include "nary_trees.h"

/**
 * nary_tree_insert - inserts a node in a N-ary tree
 * @parent: pointer to the parent node (of inserted one)
 * @str: string to be stored in that node (duplicated)
 * Return: pointer to created node / NULL on failure 
*/

nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new = malloc(sizeof(*new));

	if (!new)
		return (fprintf(stderr, "Failed to alloc memory for a new node\n"), NULL);
	
	new->parent = parent;
	new->content = strdup(str);
	new->nb_children = 0;
	new->children = new->next = NULL;

	if (parent != NULL)
	{
		new->next = parent->children;
		parent->children = new;
		++(parent->nb_children);
	}
	return (new);
}


