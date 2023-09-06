#include <string.h>
#include "pathfinding.h"

static char *visited;
static queue_t *path;
static vertex_t const *target_city;
static graph_t *g;

queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
							vertex_t const *target)
{
	queue_t *backpath = NULL;

	setbuf(stdout, NULL);

	visited = calloc(graph->nb_vertices, sizeof(*visited));
	path = queue_create();
	if (!visited || !path)
		return (NULL);
	target_city = target;
	g = graph;

	if (backtrack(start))
	{
		char *city;

		backpath = queue_create();
		while ((city = dequeue(path)))
			queue_push_front(backpath, city);
	}
	queue_delete(path);
	free(visited);
	return (backpath);
}

int backtrack(vertex_t const *curr)
{
	char *content = NULL;
	edge_t *ed = NULL;

	if (visited[curr->index])
		return (0);
	printf("Checking %s\n", curr->content);
	visited[curr->index] = 1;

	content = strdup(curr->content);
	queue_push_front(path, content);
	if (curr == target_city)
		return (1);

	ed = curr->edges;
	while (ed)
	{
		if (backtrack(ed->dest))
			return (1);
		ed = ed->next;
	}
	free(dequeue(path));
	return (0);
}
