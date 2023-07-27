#include "graphs.h"
/**
 * max - quick function to compute max
 * @a: first contender
 * @b: second contender
 * Return: the winner (takes it all)
 */

size_t max(size_t a, size_t b)
{
	return (a > b ? a : b);
}

/**
 * dfs_recurs - recursive funtion to stackify to depth-first traversal
 * of graph
 * @curr: pointer to vertex traversed
 * @depth: depth of visited vertex
 * @marked: array of int to keep track of visited vertex
 * @action: pointer to function to be called for each visited vertex
 * Return: max depth of graph depth-firstized, or 0 if failure/goes wrong
 */

size_t dfs_recurs(vertex_t *curr, size_t depth, int *marked,
				  void (*action)(const vertex_t *v, size_t depth))
{
	edge_t *ed = NULL;
	size_t max_depth = depth;

	if (!curr || marked[curr->index] == 1)
		return (depth > 1 ? depth - 1 : 0);
	marked[curr->index] = 1;
	action(curr, depth);

	for (ed = curr->edges; ed; ed = ed->next)
		max_depth = max(dfs_recurs(ed->dest, depth + 1, marked, action), max_depth);
	return (max_depth);
}

/**
 * depth_first_traverse - goes through a graph using depth-first algorithm
 * @graph: pointer to the graph to depth-first's
 * @action: pointer to a function to be called for each visited vertex
 * => v => const pointer to visited vertex
 * => depth => depth of v, from starting vertex
 * Return: biggest vertex depth, or 0 on failure
 *
 * EYNTK concept page told us that "its index [...] will help us for future
 * algorithms....;) Nihihihiiii" <= is it the moment ?
 *
 */

size_t depth_first_traverse(const graph_t *graph,
							void (*action)(const vertex_t *v, size_t depth))
{
	size_t max_depth = 0;
	int *marked = NULL;
	/* to keep track of visited vertex */
	if (!graph)
		return (0);
	marked = calloc(graph->nb_vertices, sizeof(*marked));
	if (!marked)
		return (0);

	max_depth = max(dfs_recurs(graph->vertices, 0, marked, action), max_depth);
	free(marked);
	return (max_depth);
}
