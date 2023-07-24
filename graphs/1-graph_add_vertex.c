#include "graphs.h"

/**
 * graph_add_vertex - adds a vertex to an existing graph
 * @graph: pointer to graph to add to
 * @str: string to store in new vertex
 * Return: NULL if failure, else pointer to new vertex
*/

vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *vertex, *new;

	vertex = graph->vertices;
	while (vertex)
	{
		if (!strcmp(vertex->content, str))
			return (NULL);
		if (!vertex->next)
			break;
		vertex = vertex->next;
	}
	new = malloc(sizeof(vertex_t));
	if (!new)
		return (NULL);
	new->content = strdup(str);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->index = (graph->nb_vertices)++;
	new->next = NULL;
	/* if at least one vertex // else new becomes head */
	if (vertex)
		vertex->next = new;
	else
		graph->vertices = new;
	return (new);
}
