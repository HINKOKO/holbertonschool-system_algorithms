#include "rb_trees.h"

/**
 * array_to_rb_tree - builds a RBT from an array
 * using hard task 2 function and yeksss !
 * @array: pointer to first element of array
 * @size: number of element in the array
 * Return: pointer to root node because we are gentlemens
 * NULL otherwise for the same reasons
 *
 */

rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	size_t i;
	rb_tree_t *groot = NULL;

	for (i = 0; i < size; i++)
		rb_tree_insert(&groot, array[i]);
	return (groot);
}
