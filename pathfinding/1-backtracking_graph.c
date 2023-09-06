#include <string.h>

#include "pathfinding.h"

int backtrack_helper(queue_t *path, char *visited, vertex_t const *current,
					 vertex_t const *target)
{
	edge_t *ed = NULL;
	vertex_t *vrt = NULL;
	char *content = NULL;

	if (!current) /* last || avoid already visited */
		return (0);

	printf("Checking %s\n", current->content);

	content = strdup(current->content);
	queue_push_front(path, (void *)content);
	if (current->content == target->content)
		return (1);

	visited[current->index] = 1;
	/* edges point to head node of LL of edges, browse them */
	for (ed = current->edges; ed; ed = ed->next)
	{
		vrt = ed->dest;
		if (!visited[current->index] && backtrack_helper(path, visited, vrt, target))
			return (1);
	}
	free(dequeue(path));
	return (0);
}
/**
 * backtracking_graph - search for the first path from start to target in a graph
 *
 * @graph: pointer to the graph
 * @start: pointer to starting vertex
 * @targer: pointer to desired vertex to reach
 *
 * Return: must return a queue, with each node (char *) corresponding
 * to a vertex, forming a path from 'start' to 'target'
 *
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start, vertex_t const *target)
{
	queue_t *path_track = queue_create(), *final_queue = queue_create();
	char *visited = NULL;
	char *content = NULL;

	visited = calloc((int)graph->nb_vertices, sizeof(char));
	if (!visited)
		return (NULL);

	if (!backtrack_helper(path_track, visited, start, target))
	{
		while (path_track->front)
			free(dequeue(path_track));
		free(path_track), free(final_queue);
		path_track = NULL, final_queue = NULL;
	}
	else
	{
		while ((content = dequeue(path_track)))
			queue_push_front(final_queue, (void *)content);
		free(path_track);
	}
	free(visited);
	return (final_queue);
}
