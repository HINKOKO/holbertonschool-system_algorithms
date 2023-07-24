#include "graphs.h"

int connect_edge(vertex_t *start, vertex_t *dest, edge_type_t type);

/**
 * connect_edge - helper function to continue adding edge
 * after finding src and dest position
 * @start: the source vertex
 * @dest: the end vertex
 * @type: the type of edges to create
 * Return: NULL if failure, success: pointer to new edge
*/

int connect_edge(vertex_t *start, vertex_t *dest, edge_type_t type)
{
	edge_t *new, *tmp = NULL;

	if (!start || !dest)
		return (-1);

	for (tmp = start->edges; tmp && tmp->next; tmp = tmp->next)
		;
	new = calloc(1, sizeof(edge_t));
	if (!new)
		return (-1);
	/* we reach the end of LL of edges */
	if (tmp)
		tmp->next = new;
	else
		start->edges = new;
	new->dest = dest;
	new->next = NULL;
	++start->nb_edges;

	if (type == BIDIRECTIONAL)
		connect_edge(dest, start, UNIDIRECTIONAL);
	return (1);
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
	vertex_t *tmp, *start, *end = NULL;

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
	if (connect_edge(start, end, type) == -1)
		return (0);
	else
		return (1);
}
