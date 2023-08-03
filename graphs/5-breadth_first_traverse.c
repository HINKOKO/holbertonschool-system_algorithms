#include "graphs.h"

/**
 * breadth_first_traverse - goest through a graph using breadth-first
 * @graph: pointer to graph to breadth-first'ss
 * @action: pointer to a function to be called for each visited vertex
 * Return: biggest vertex depth, or 0 on failure
 */

size_t breadth_first_traverse(const graph_t *graph,
							  void (*action)(const vertex_t *v, size_t depth))
{
	size_t depth = 0, next_b = 0, b_size = 1;
	char *mark = NULL;
	vertex_t **vrtx;
	edge_t *ed;
	int i, j = 1;

	if (!graph || !graph->nb_vertices)
		return (0);

	mark = calloc(graph->nb_vertices, sizeof(char));
	vrtx = calloc(graph->nb_vertices, sizeof(vertex_t *));

	vrtx[0] = graph->vertices;
	mark[0] = 1;

	/* outer loop to go through all vertex in main LL */
	for (i = 0; vrtx[i]; i++)
	{
		action(vrtx[i], depth);
		/* inner loop to go through LL of edges paths */
		for (ed = vrtx[i]->edges; ed; ed = ed->next)
		{
			/* vertex found and not seen already */
			if (mark[ed->dest->index] == 0)
			{
				vrtx[j++] = ed->dest;
				mark[ed->dest->index] = 1;
				next_b += 1;
			}
		}
		if (--b_size == 0)
		{
			depth++, b_size = next_b;
			next_b = 0;
		}
	}
	free(mark), free(vrtx);
	return (depth - 1);
}
