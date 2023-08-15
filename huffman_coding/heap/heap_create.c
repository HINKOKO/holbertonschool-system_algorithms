#include "heap.h"

/**
 * heap_create - creates a Heap data struct
 * @data_cmp: pointer to a comparison function
 * => takes two void parameters, each one being the data stored in a node
 * => return the difference between the two data stored at those pointers
 * used to determine is a node's value is greater or lower than another, so
 * that we can build our heap
 *
 * Return: A pointer to the created heap_t struct or NULL on failure
 */

heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *new_heap = NULL;

	(void)data_cmp;

	new_heap = malloc(sizeof(*new_heap));
	if (!new_heap)
		return (NULL);

	new_heap->root = NULL;
	new_heap->size = 0;
	new_heap->data_cmp = data_cmp;

	return (new_heap);
}
