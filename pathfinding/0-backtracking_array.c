#include "pathfinding.h"

static char **visited;

/**
 * valid_move - checks if intended is valid (boundaries ,walls, already been ?)
 *
 * @map: pointer to read_only 2D array
 * @rows: number of rows
 * @cols: number of cols
 * @step: pointer to current point stepping
 *
 * Return: 1 for valid step, 0 for invalid step
 */

int valid_move(char **map, int rows, int cols, const point_t *step)
{
	if (!(step->x >= 0 && step->x < rows && step->y >= 0 && step->y < cols))
		return (0);

	/* check for "rock cells", walls , poison... */
	if (map[step->x][step->y] == '1')
		return (0);
	/* protect from visited cells */
	if (visited[step->x][step->y])
		return (0);

	return (1);
}

/**
 * add_to_path - add valid point to the path
 *
 * @path: pointer to queue to add to
 * @curr: pointer to point to be added
 *
 * Return: 1 for success , 0 otherwise
 */

int add_to_path(queue_t *path, point_t const *curr)
{
	point_t *new = NULL;

	new = malloc(sizeof(point_t));
	if (!new)
		return (0);
	new->x = curr->x;
	new->y = curr->y;

	queue_push_front(path, (void *)new);
	return (1);
}

/**
 * find_path_dfs - helper function behaving in DFS way
 * to perform backtracking in clockwise order
 * RIGHT BOTTOM LEFT UP
 * @path: pointer to queue
 * @visited: "record" of visited cells
 * @map: pointer to read-only 2D array
 * @rows: number of rows in map
 * @cols: number of cols in map
 * @curr: pointer to current cell being visited
 * @target: pointer to desired cell to reach
 *
 * Return: 0 always success
 */

int find_path_dfs(queue_t *path, char **visited, char **map, int rows,
				  int cols, point_t const *curr, point_t const *target)
{
	point_t step[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int i, found = 0;

	for (i = 0; i < 4; i++)
	{
		step[i].x += curr->x;
		step[i].y += curr->y;
	}
	printf("Checking coordinates [%d, %d]\n", curr->x, curr->y);
	visited[curr->y][curr->x] = 1;

	if (curr->x == target->x && curr->y == target->y)
		return (add_to_path(path, curr));

	for (i = 0; !found && i < 4; i++)
	{
		if (valid_move(map, rows, cols, step + i))
		{
			found |= find_path_dfs(path, visited, map, rows, cols, step + i, target);
		}
	}
	if (found)
		return (add_to_path(path, curr));
	return (0);
}
/**
 * backtracking_array - search for first path in map from start to target
 * => map used as a graph
 * @map: pointer to read-only 2D array
 * @rows: number of rows in map
 * @cols: number of cols in map
 * @start: pointer to current cell being visited
 * @target: pointer to desired cell to reach
 *
 * Return: pointer to queue representing the correct path
 */

queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target)
{
	queue_t *path = NULL;
	int i;

	if (!map || !rows || !cols || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);
	visited = calloc(rows, sizeof(char));

	for (i = 0; i < rows; i++)
		visited[i] = calloc(cols, sizeof(char));

	if (!find_path_dfs(path, visited, map, rows, cols, start, target))
	{
		while (path->front)
			free(dequeue(path));
		queue_delete(path);
		return (NULL);
	}
	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);
	return (path);
}
