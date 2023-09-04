#include <stdbool.h>

#include "pathfinding.h"

bool is_valid(queue_t *path, char **map, char **visited, int rows, int cols, point_t *next)
{
	if (!next->x >= 0 && next->x < rows && next->y >= 0 && next->y < cols && map[next->y][next->x] == '0')
		return (0);

	if (map[next->x][next->y] == '1')
		return (0);

	/* step in a visited cell ? */
	if (visited[next->x][next->y])
		return (0);

	return (1);
}

bool find_path(char **map, int rows, int cols,
			   point_t const *curr, point_t const *target, queue_t *path, char **visited)
{
	int i, found = 0;
	point_t next[4] = {{+1, 0}, {0, +1}, {-1, 0}, {0, -1}};
	/* coordinates like naval war respectively to RIGHT BOTTOM LEFT UP */

	for (i = 0; i < 4; i++)
	{
		next[i].x += curr->x;
		next[i].y += curr->y;
	}

	printf("Checking coordinates [%d, %d]\n", curr->x, curr->y);
	visited[curr->x][curr->y] = 1;

	if (curr->x == target->x && curr->y == target->y)
		return (queue_push_front(path, (void *)curr));

	for (i = 0; !found && i < 4; i++)
	{
		if (is_valid(path, map, visited, rows, cols, next + i))
			found |= find_path(map, rows, cols, next + i, target, path, visited);
	}
	if (found)
		return (queue_push_front(path, (void *)curr));
	return (0);
}

/**
 * backtracking_array - searches for first path from starting point
 * to a target within two-dim array
 *
 * @map: pointer to Read-only 2D array
 * @rows: number of rows
 * @cols: number of hey, cols
 * @start: coordinates of starting point
 * @target: coordinates of target point
 *
 * Return: a queue struct, in which each node is a point in the path from
 * start to => target
 *
 * ORDER IS:
 *  RIGHT - BOTTOM - LEFT - TOP
 */

queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target)
{
	int i;
	char **visited = NULL;
	queue_t *first_path = queue_create();

	visited = malloc(sizeof(char *) * rows);
	if (!visited)
	{
		free(first_path);
		return (NULL);
	}
	for (i = 0; i < rows; i++)
		visited[i] = calloc(cols, sizeof(char));

	if (!find_path(map, rows, cols, start, target, first_path, visited))
	{
		queue_delete(first_path);
		first_path = NULL;
	}
	free(visited);
	return (first_path);
}
