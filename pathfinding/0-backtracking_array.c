#include "pathfinding.h"

int is_valid(queue_t *path, char **map, char **visited, int rows, int cols, const point_t *next)
{
	if (!path || !map || !visited || !rows || !cols || !next)
		return (0);

	if (!((next->x >= 0 && next->x < cols) && (next->y >= 0 && next->y < rows)))
		return (0);

	if (map[next->x][next->y] == '1')
		return (0);

	/* step in a visited cell ? */
	if (visited[next->y][next->x])
		return (0);

	return (1);
}

/**
 * add_point - adds a point_t point to the queue that represent
 * first path found by backtracking trick
 *
 * @path: queue of nodes already visited
 * @current: current (valid) point we wanna add
 * Return: 1 for success, 0 for failure
 */

int add_point(queue_t *path, const point_t *current)
{
	point_t *new = NULL;

	/* sanity check */
	if (!path || !current)
		return (0);

	new = malloc(sizeof(point_t));
	if (!new)
		return (0);

	new->x = current->x, new->y = current->y;

	if (!queue_push_front(path, (void *)current))
	{
		free(new);
		return (0);
	}

	return (1);
}

/**
 * find_path_dfs - recursive function to backtrack the array
 * RIGHT BOTTOM LEFT UP order
 * @map: pointer to read-only array 2D
 * @rows: number of rows in map
 * @cols: number of cols in map
 * @curr: pointer to current cell visited
 * @target: pointer to objective
 * @path: pinter to queue of visited nodes
 * @visited: pointer to side 2D array to keep track of visited cell
 *
 * Return: 1 for success (target found), 0 if not
 */

int find_path_dfs(char **map, int rows, int cols,
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
	visited[curr->y][curr->x] = 1;

	if (curr->x == target->x && curr->y == target->y)
		return (add_point(path, curr));

	for (i = 0; !found && i < 4; i++)
	{
		if (is_valid(path, map, visited, rows, cols, next + i))
			found |= find_path_dfs(map, rows, cols, next + i, target, path, visited);
	}
	if (found)
		return (add_point(path, curr));
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
	int i, j;
	char **visited = NULL;
	queue_t *backpath = NULL;

	backpath = queue_create();
	visited = malloc(sizeof(char *) * rows);
	if (!visited)
	{
		free(backpath);
		return (NULL);
	}
	for (i = 0; i < rows; i++)
		visited[i] = calloc(cols, sizeof(char));
	if (!visited[i])
	{
		for (j = 0; j < i; j++)
			free(visited[i]);
		free(visited);
		free(backpath);
		return (NULL);
	}

	if (!find_path_dfs(map, rows, cols, start, target, backpath, visited))
	{
		while (backpath->front)
			free(dequeue(backpath));
		queue_delete(backpath);
		backpath = NULL;
	}
	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);
	return (backpath);
}
