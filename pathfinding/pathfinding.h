#ifndef __PATHFINDER__
#define __PATHFINDER__

#include <stdio.h>
#include <stdlib.h>

#include "queues.h"
#include "graphs.h"

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordina
 *
 */

typedef struct point_s
{
	int x;
	int y;
} point_t;

/* queue stuff on my side for testing*/

queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target);
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
							vertex_t const *target);
int backtrack(vertex_t const *curr);

/* Dijkstra's stuff */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
						vertex_t const *target);

#endif /* __PATHFINDER__ */
