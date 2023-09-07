#include "pathfinding.h"

#include <sys/types.h>
#include <string.h>

/* infinite 'distance' from computerphile => INT_MAX usage*/
#include <limits.h>

queue_t *pathfinder(vertex_t **predecessors, vertex_t const *target)
{
	queue_t *path = queue_create();
	vertex_t const *current = target;

	if (!path || !predecessors[target->index])
		return (NULL);

	while (current)
	{
		queue_push_front(path, (void *)current);
		current = predecessors[current->index];
	}
	return (path);
}

void compute_dist(graph_t *graph, vertex_t const *start,
				  int *map, size_t *dist, vertex_t **predecessors)
{
	/* size_t i; */
	vertex_t *curr, *neighbor;
	edge_t *edge;
	queue_t *q = queue_create(); /* to keep track of visited ones */

	(void)graph;
	if (!q)
		return;

	queue_push_front(q, (void *)start);
	while (q->front)
	{
		curr = dequeue(q);
		edge = curr->edges;
		printf("Checking %s, distance from %s is %lu", curr->content,
			   start->content, dist[curr->index]);
		while (edge)
		{
			neighbor = edge->dest;
			if (dist[curr->index] + edge->weight < dist[neighbor->index])
			{
				dist[neighbor->index] = dist[curr->index] + edge->weight;
				predecessors[neighbor->index] = curr;
				if (!map[neighbor->index])
				{
					queue_push_front(q, (void *)neighbor);
					map[neighbor->index] = 1;
				}
			}
			edge = edge->next;
		}
	}
	queue_delete(q);
}

/**
 * dijkstra_graph - uses Dijkstra's Algo to find path
 * @graph: pointer to graph struct
 * @start: pointer to starting vertex
 * @target: pointer to target vertex
 * Return: path queue or NULL
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
						vertex_t const *target)
{
	vertex_t **predecessors;
	size_t *dist;
	int *map;

	if (!graph || !start || !target)
		return (NULL);

	map = calloc(graph->nb_vertices, sizeof(*map));
	dist = malloc(graph->nb_vertices * sizeof(*dist));
	predecessors = calloc(graph->nb_vertices, sizeof(**predecessors));

	if (!map || !dist || !predecessors)
		return (NULL);

	/* consider at beginning that all distances are Infinite */
	/* fill memory with constant byte fills n bytes pointed by s with c 'scn'*/
	memset(dist, 0xFF, graph->nb_vertices * sizeof(*dist));
	/* set start to be the first and distance 0*/
	dist[start->index] = 0;

	compute_dist(graph, start, map, dist, predecessors);

	free(map), free(dist);

	return (pathfinder(predecessors, target));
}
