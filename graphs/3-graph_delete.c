#include "graphs.h"

/**
 * graph_delete - delete all the vertices and edges
 * and the graph itself, "table rase in French"
 * @graph: pointer to the graph to delete
 *
 * v for vertex and tmp_v for temp vertex, mecanics of free-age
 * e for edge and tmp_e temp edge, mecanics of free-age
 */

void graph_delete(graph_t *graph)
{
	vertex_t *v, *tmp_v;
	edge_t *e, *tmp_e;

	if (!graph)
		return;
	v = graph->vertices;
	while (v)
	{
		tmp_v = v->next;
		if (v->content)
			free(v->content);
		e = v->edges;
		while (e)
		{
			tmp_e = e->next;
			free(e);
			e = tmp_e;
		}
		free(v);
		v = tmp_v;
	}
	free(graph);
}
