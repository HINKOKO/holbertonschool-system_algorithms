#include "graphs.h"

/**
 * graph_create - allocates memory to store a graph_t struct
 * & initialize its content
 * Return: NULL on failure || pointer to alloc'ed struct
 */

graph_t *graph_create(void)
{
	graph_t *new = malloc(sizeof(graph_t));

	if (!new)
		return (NULL);
	new->nb_vertices = 0;
	new->vertices = NULL;
	return (new);
}
