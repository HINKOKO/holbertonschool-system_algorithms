#include <limits.h>
#include <string.h>

#include "pathfinding.h"

#define COLOR "\033[32m"
#define RESET "\033[0m"
#define INF 0xFFFF

/**
 * pick_min_vertex - finds the lowest weighted vertex from src to it
 * @graph: pointer to graph
 * @dist: pointer to array of distance from start vertex
 * @seen: pointer to array of visited vertices
 * @idx: current index
 *
 * Return: vertex index with min weight from src to it
 */

vertex_t *pick_min_vertex(graph_t *graph, size_t *dist, size_t *seen, size_t *idx)
{
	size_t i, min = INF;
	vertex_t *v;

	v = graph->vertices;
	*idx = INF;
	for (i = 0; i < graph->nb_vertices; i++)
	{
		if (seen[i] == 0 && min > dist[i])
		{
			min = dist[i];
			*idx = i;
		}
	}
	if (*idx == INF)
		return (NULL); /* No better dist thant infinite has been found */
	while (v->next)
	{
		if (v->index == *idx)
			return (v);
		v = v->next;
	}
	return (v);
}

/**
 * edgar_dijkstra - performs a recursive call to Dijkstra main logic
 * => From the vertex we are, we select the min cost buddy vertex
 * which becomes 'curr' vertex
 * => Then go through the edges of that curr, record the 'seen'ing of those
 * => update the 'best-so-far' distances for vertices with edges from curr
 *
 */

void edgar_dijkstra(graph_t *graph, size_t *dist, size_t *seen, vertex_t **path_via,
					vertex_t const *start, vertex_t const *target, size_t idx)
{
	vertex_t *curr;
	edge_t *edge;
	size_t i = 0, tmp;

	curr = pick_min_vertex(graph, dist, seen, &idx);
	if (!curr)
		return;
	printf("Checking %s, distance from %s is %ld\n", curr->content, start->content, dist[curr->index]);
	i = curr->index;
	edge = curr->edges;
	while (edge && seen[i] == 0)
	{
		tmp = dist[i] + edge->weight;
		if (dist[edge->dest->index] > tmp)
		{
			printf("dist index mystery => %ld\n", dist[edge->dest->index]);
			dist[edge->dest->index] = tmp;
			path_via[edge->dest->index] = curr;
		}
		edge = edge->next;
	}
	seen[i] = 1;
	if (seen[target->index] == 1)
		return; /* we're done, at some point */
	edgar_dijkstra(graph, dist, seen, path_via, start, target, idx);
}

/**
 * add_to_path - add cheapest vertices to the shortest path to be found
 * @graph: pointer to graph
 * @path: pointer to queue structure
 * @path_via: pointer to vertices we are about to add to queue
 * @start: pointer to starting vertex
 * @target: pointer to destination vertex
 */

void add_to_path(graph_t *graph, queue_t *path, vertex_t **path_via,
				 vertex_t const *start, vertex_t const *target)
{
	size_t i = target->index;
	size_t size = graph->nb_vertices;
	printf("size is therefor => %ld\n", size);
	printf("what is i in add_to_path => %ld\n", i);
	if (!path_via[i])
		return;

	while (path_via[i] && i < graph->nb_vertices)
	{
		if (!queue_push_front(path, strdup(path_via[i]->content)))
			queue_delete(path);
		i = path_via[i]->index;
		printf("start index is what john => %ld\n", start->index);
		if (i == start->index)
			return;
	}
}

/**
 * dijkstra_graph - Search for shortest path in weighted graph
 * using Dijkstra algorithm
 *
 * @graph: pointer to the graph to go through
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: a queue, each node content a (char * ) corresponding to a vertex
 * representing path from start to end
 */

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target)
{
	size_t *dist = 0, *seen = 0;
	size_t size = 0;
	vertex_t **path_via = NULL;
	queue_t *q = queue_create();

	seen = calloc(graph->nb_vertices, sizeof(*seen));
	path_via = calloc(graph->nb_vertices, sizeof(**path_via));
	dist = calloc(graph->nb_vertices, sizeof(*dist));

	if (!dist || !path_via || !seen)
		return (fprintf(stderr, "Lost in graph Abort Mayday"), NULL);

	size = graph->nb_vertices;
	memset(dist, INF, size * sizeof(*dist));
	dist[start->index] = 0;
	edgar_dijkstra(graph, dist, seen, path_via, start, target, 0);
	add_to_path(graph, q, path_via, start, target);
	free(seen), free(dist), free(path_via);

	return (q);
}
