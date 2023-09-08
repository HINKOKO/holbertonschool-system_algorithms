#include <stdlib.h>
#include <stdio.h>

#include "../pathfinding.h"

/**
 * print_free_path - Unstacks the queue to discover the path from the starting
 * vertex to the target vertex. Also deallocates the queue.
 *
 * @path: Queue containing the path
 */
static void print_free_path(queue_t *path)
{
    printf("Path found:\n");
    while (path->front)
    {
        char *city = (char *)dequeue(path);
        printf(" %s\n", city);
        free(city);
    }
    free(path);
}

/**
 * main - A simple graph to test Backtracking algorithm
 *
 * Return: Either EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    graph_t *graph;
    vertex_t *start, *target;
    queue_t *path;

    graph = graph_create();
    graph_add_vertex(graph, "San Francisco");
    graph_add_vertex(graph, "Los Angeles");
    graph_add_vertex(graph, "Las Vegas");
    start = graph_add_vertex(graph, "Seattle");
    graph_add_vertex(graph, "Chicago");
    graph_add_vertex(graph, "Washington");
    graph_add_vertex(graph, "New York");
    graph_add_vertex(graph, "Houston");
    graph_add_vertex(graph, "Nashville");
    target = graph_add_vertex(graph, "Miami");
    graph_add_edge(graph, "San Francisco", "Los Angeles", BIDIRECTIONAL);
    graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL);
    graph_add_edge(graph, "Los Angeles", "Las Vegas", BIDIRECTIONAL);
    graph_add_edge(graph, "San Francisco", "Seattle", BIDIRECTIONAL);
    graph_add_edge(graph, "Seattle", "Chicago", BIDIRECTIONAL);
    graph_add_edge(graph, "Chicago", "Washington", BIDIRECTIONAL);
    graph_add_edge(graph, "Washington", "New York", BIDIRECTIONAL);
    graph_add_edge(graph, "Las Vegas", "Houston", BIDIRECTIONAL);
    graph_add_edge(graph, "Houston", "Nashville", BIDIRECTIONAL);
    graph_add_edge(graph, "Nashville", "Washington", BIDIRECTIONAL);
    graph_add_edge(graph, "Nashville", "Miami", BIDIRECTIONAL);

    path = backtracking_graph(graph, start, target);
    if (!path)
    {
        fprintf(stderr, "Failed to retrieve path\n");
        return (EXIT_FAILURE);
    }

    print_free_path(path);
    graph_delete(graph);

    return (EXIT_SUCCESS);
}
