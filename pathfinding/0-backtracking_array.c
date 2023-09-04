#include "pathfinding.h"
/* malloc calloc free */
#include <stdlib.h>
/* printf */
#include <stdio.h>

/**
 * valid_move - validates next possible step in a maze map grid
 *
 * @path: queue of nodes visited, represents current candidate solution
 * @map: pointer to a read-only two-dimensional array (0 represents a
 *   walkable cell, 1 represents a blocked cell)
 * @visited: pointer to a two-dimensional array recording which coordinate
 *   postions have already been visited
 * @rows: count of rows in map
 * @cols: count of columns in map
 * @step: coordinates of potential next map cell
 * Return: 1 if step is valid, 0 if not or failure
 */
int valid_move(queue_t *path, char **map, char **visited, int rows,
			   int cols, const point_t *step)
{
	if (!path || !map || !visited || !rows || !cols || !step)
		return (0);

	if (!((step->x >= 0 && step->x < cols) &&
		  (step->y >= 0 && step->y < rows)))
		return (0);

	if (map[step->y][step->x] == '1')
		return (0);

	if (visited[step->y][step->x])
		return (0);

	return (1);
}

/**
 * addPointToPath - adds a map point in a 2D grid to the queue representing
 *   the first backtracking solution found in RDLU order; expects to build
 *   path from target to origin
 *
 * @path: queue of nodes visited, represents current candidate solution
 * @curr: coordinates of current map cell
 * Return: 1 on success, 0 on failure
 */
int addPointToPath(queue_t *path, const point_t *curr)
{
	point_t *new = NULL;

	if (!path || !curr)
		return (0);

	new = malloc(sizeof(point_t));
	if (!new)
		return (0);

	new->x = curr->x;
	new->y = curr->y;

	if (!queue_push_front(path, (void *)new))
	{
		free(new);
		return (0);
	}

	return (1);
}

/**
 * find_path_dfs - recursive helper to backtrack_array, searches for the
 *   first path from a starting point to a target point within a
 *   two-dimensional array using a recursive flood-fill in RDLU order
 *
 * @path: queue of nodes visited, represents current candidate solution
 * @map: pointer to a read-only two-dimensional array (0 represents a
 *   walkable cell, 1 represents a blocked cell)
 * @visited: pointer to a two-dimensional array recording which coordinate
 *   postions have already been visited
 * @rows: count of rows in map
 * @cols: count of columns in map
 * @curr: coordinates of current map cell
 * @target: coordinates of the target point
 * Return: 1 if target found in current recursion frame, 0 if not or failure
 */
int find_path_dfs(queue_t *path, char **map, char **visited, int rows,
				  int cols, const point_t *curr, const point_t *target)
{
	point_t next_step[4] = {{+1, 0}, {0, +1}, {-1, 0}, {0, -1}};
	int i, target_found = 0;

	if (!path || !map || !visited || !rows || !cols || !curr || !target)
		return (0);

	for (i = 0; i < 4; i++)
	{
		next_step[i].x += curr->x;
		next_step[i].y += curr->y;
	}
	printf("Checking coordinates [%i, %i]\n", curr->x, curr->y);
	visited[curr->y][curr->x] = 1;

	if (curr->x == target->x && curr->y == target->y)
		return (addPointToPath(path, curr));

	for (i = 0; !target_found && i < 4; i++)
	{
		if (valid_move(path, map, visited, rows, cols, next_step + i))
		{
			target_found |= find_path_dfs(path, map, visited,
										  rows, cols,
										  next_step + i, target);
		}
	}

	if (target_found)
		return (addPointToPath(path, curr));

	return (0);
}

queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target)
{
	queue_t *backpath = NULL;
	char **visited = NULL;
	int i, j;

	if (!map || !rows || !cols || !start || !target)
		return (NULL);

	backpath = queue_create();
	if (!backpath)
		return (NULL);
	visited = malloc(sizeof(char *) * rows);
	if (!visited)
	{
		free(backpath);
		return (NULL);
	}
	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(char));
		if (!visited[i])
		{
			for (j = 0; j < i; j++)
				free(visited[i]);
			free(visited);
			free(backpath);
			return (NULL);
		}
	}
	if (!find_path_dfs(backpath, map, visited, rows, cols, start, target))
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
