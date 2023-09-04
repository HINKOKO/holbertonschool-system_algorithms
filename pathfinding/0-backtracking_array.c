#include <stdbool.h>

#include "pathfinding.h"

bool is_valid(char **map, int rows, int cols, int x, int y)
{
	return (x >= 0 && x < rows && y >= 0 && y < cols && map[x][y] == '0');
}

bool find_path(char **map, int rows, int cols,
			   point_t const *start, point_t const *target, queue_t *path)
{
	point_t *new = NULL;
	int i, newX, newY;
	int x = start->x;
	int y = start->y;
	int dx[] = {0, 1, 0, -1};
	int dy[] = {1, 0, -1, 0};

	new = malloc(sizeof(point_t));

	if (x == target->x && y == target->y)
	{
		queue_push_front(path, (void *)start);
		return (1);
	}
	/* order of exploration RIGHT BOTTOM LEFT TOP*/

	for (i = 0; i < 4; i++)
	{
		newX = x + dx[i];
		newY = y + dy[i];

		if (is_valid(map, rows, cols, newX, newY))
		{
			/* mark cell as visited */
			map[newX][newY] = '1';
			point_t new = {newX, newY};
			if (find_path(map, rows, cols, &new, target, path))
			{
				queue_push_front(path, (void *)start);
				return (1);
			}

			map[newX][newY] = '0'; /* backtrack if path not found */
		}
	}
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
	queue_t *first_path = queue_create();

	if (find_path(map, rows, cols, start, target, first_path))
		return (first_path);
	else
	{
		free(first_path);
		return (NULL);
	}
}
