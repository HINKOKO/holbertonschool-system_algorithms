#include "graphs.h"

edge_t *connect_edge(vertex_t *start, vertex_t *end);

/**
 * connect_edge - helper function to continue adding edge
 * after finding src and dest position
 * @start: the source vertex to connect from
 * @end: the end vertex to connect to
 * Return: NULL if failure, success: pointer to new edge
*/

edge_t *connect_edge(vertex_t *start, vertex_t *end)
{
	edge_t *new = NULL, *tmp = NULL;

	if (!start || !end)
		return (NULL);
	new = calloc(1, sizeof(edge_t));
	if (!new)
		return (NULL);
	new->dest = end;
	new->next = NULL;

	for (tmp = start->edges; tmp && tmp->next; tmp = tmp->next)
		;
	/* we reach the end of LL of edges */
	if (tmp)
		tmp->next = new;
	else
		start->edges = new;
	++start->nb_edges;

	return (new);
}

/**
 * graph_add_edge - adds an edge between two vertices
 * to an existing graph
 * @graph: pointer to the graph to add the edge to
 * @src: string identifying the vertex to make the connection from
 * @dest: string identifying the vertex to connect to
 * @type: type of the edge UNI or BIDIRECTIONAL
 *
 * Return: 1 on success (continuing) 0 on failure
*/

int graph_add_edge(graph_t *graph, const char *src,
	const char *dest, edge_type_t type)
{
	vertex_t *tmp = NULL, *start = NULL, *end = NULL;

	if (!graph || !src || !dest)
		return (0);
	/* find src */
	for (tmp = graph->vertices; tmp; tmp = tmp->next)
	{
		if (!strcmp(tmp->content, src))
			start = tmp;
		else if (!strcmp(tmp->content, dest))
			end = tmp;
	}
	/* if either 'src' or 'dest' is not found, abort */
	if (!start || !end)
		return (0);
	if (!connect_edge(start, end))
		return (0);
	if (type == BIDIRECTIONAL)
	{
		if (!connect_edge(end, start))
			return (0);
	}
	return (1);
}
