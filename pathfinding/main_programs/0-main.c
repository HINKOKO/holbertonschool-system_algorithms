#include <stdlib.h>
#include <stdio.h>

#include "../pathfinding.h"

/**
 * print_free_path - Unstacks the queue to discover the path
 * from starting vertex. Also deallocaters the queue
 *
 * @path: Queue containing the path
 */

static void printf_free_path(queue_t *path)
{
	printf("Path found:\n");
	while (path->front)
	{
		point_t *point = dequeue(path);
		printf(" [%d, %d]\n", point->x, point->y);
		free(point);
	}
	free(path);
}

/**
 * main - Backtracking using an array. Here the array is chosen to demonstrate
 * That Backtracking is a really bad algorithm. The target point is just
 * dow-right from the starting point, but since => we first check the
 * RIGHT cell, then TOP, then LEFT, then BOTTOM, our algo will almost go through
 * the whole maze before finding a path. Don"t use backtracking, Just dont.
 * Backtracking is bad, ( except for N-Queens big smart boy ? )
 */

int main(void)
{
	char *map[21] = {
		"111111111111111111111",
		"101000000000001000001",
		"101011111111101110101",
		"100010000010001000101",
		"111111111010111011101",
		"101000000010100010001",
		"101011111010111011111",
		"101000001010001000001",
		"101110111011101111101",
		"101000001000100000101",
		"101011111110111110101",
		"101000000010000010001",
		"101111101111101111101",
		"000000001000001000001",
		"111011111010101011111",
		"100010100010101000001",
		"101110101111111110111",
		"100000101000000000001",
		"101111101011111111101",
		"100000100000000010001",
		"111110111111111111111"};

	point_t start = {0, 13};
	point_t target = {5, 20};
	queue_t *path;

	path = backtracking_array((char **)map, 21, 21, &start, &target);
	if (!path)
		return (fprintf(stderr, "Failed to retrieve path\n"), EXIT_FAILURE);

	printf_free_path(path);
	return (EXIT_SUCCESS);
}
