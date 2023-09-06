#include <string.h>
#include "pathfinding.h"

static char *visited;
static queue_t *stack;

/**
 * backtrack - helper function to recursively track the target
 *
 * @curr: pointer to current vertex being visited
 * @target: pointer to targeted vertex
 *
 * Return: 1 for success, 0 otherwise
 */

int backtrack(vertex_t const *curr, vertex_t const *target)
{
	char *content = NULL;
	edge_t *ed = NULL;

	if (visited[curr->index])
		return (0);

	printf("Checking %s\n", curr->content);
	/* mark as visited */
	visited[curr->index] = 1;

	content = strdup(curr->content);
	queue_push_front(stack, content);
	if (curr->content == target->content)
		return (1);

	ed = curr->edges;
	while (ed)
	{
		if (backtrack(ed->dest, target))
			return (1);
		ed = ed->next;
	}
	free(dequeue(stack));
	return (0);
}

/**
 * backtracking_graph - look for first path from start to target in graph
 *
 * @graph: pointer to the graph to path in
 * @start: pointer to starting point
 * @target: pointer to target desire
 *
 * Return: a queue, each node a (char *) corresponding to a vertex
 * forming together a path from start to target
 * We push to a stack-queue and pop to 'realpath' to reverse that stack
 */

queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
							vertex_t const *target)
{
	queue_t *realpath = NULL;

	setbuf(stdout, NULL);

	visited = calloc(graph->nb_vertices, sizeof(*visited));
	realpath = queue_create();
	if (!visited || !realpath)
		return (NULL);

	if (backtrack(start, target))
	{
		char *city;

		realpath = queue_create();
		while ((city = dequeue(stack)))
			queue_push_front(realpath, city);
	}
	queue_delete(stack);
	free(visited);
	return (realpath);
}
