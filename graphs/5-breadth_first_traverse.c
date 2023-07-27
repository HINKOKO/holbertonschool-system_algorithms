#include "graphs.h"

/**
 * push - push a vertex in the queue
 * @head: double pointer to head node of queue we want to push in
 * (modify such a struct -> always double pointer on head)
 * @tail: pointer to end of queue
 * @v: pointer to vertex to be added
 * Return: pointer to new elements in queue
 */

queue_t *push(queue_t **head, queue_t *tail, vertex_t *vrtx)
{
	queue_t *new_v = malloc(sizeof(queue_t));

	if (!new_v)
		return (NULL);
	new_v->next = NULL;
	new_v->v = vrtx;
	if (*head)
		tail->next = new_v;
	else
		*head = new_v;
}

/**
 * pop - performs a pop on queue // FIFO
 * @head: double pointer to head of queue we're modifying
 * Return: pointer to popped vertex
 */

vertex_t *pop(queue_t **head)
{
	queue_t *tmp;
	vertex_t *vrtx;

	if (*head)
	{
		tmp = *head;
		/* Do not loose your head */
		*head = (*head)->next;
		vrtx = tmp->v;
		free(tmp);
	}
	return (vrtx);
}

/**
 * BFS_recurs - core stuff of BFS mecanics
 * @visit: pointer to vertex being visited now
 * @visited: pointer to tracking array of visited vertex
 * @action: pointer to function call for each visited vertex
 * Return: the max breadth possibly reachable of the graph
 */

size_t BFS_recurs(vertex_t *visit, int *visited,
				  void (*action)(const vertex_t *v, size_t depth))
{
}

/**
 * breadth_first_traverse - goest through a graph using breadth-first
 * @graph: pointer to graph to breadth-first'ss
 * @action: pointer to a function to be called for each visited vertex
 * Return: biggest vertex depth, or 0 on failure
 */

size_t breadth_first_traverse(const graph_t *graph,
							  void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t max_breadth = 0;

	if (!graph)
		return (0);
	visited = malloc(sizeof(*visited) * graph->nb_vertices);
	if (!visited)
		return (0);
	max_breadth = BFS_recurs(graph->vertices, visited, action);
	free(visited);
	return (max_breadth);
}
