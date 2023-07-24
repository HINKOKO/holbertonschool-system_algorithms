#ifndef __HGRAPHS__
#define __HGRAPHS__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * enum edge_type_e - Enumarates the different types of
 * connection between two vertices
 *
 * @UNIDIRECTIONAL: The connection is made only in one way
 * @BIDIRECTIONAL: The connection is made in two ways
 */

typedef enum edge_type_e
{
	UNIDIRECTIONAL = 0,
	BIDIRECTIONAL
} edge_type_t;

/* Define the structure temporarily for usage in the edge_t */
typedef struct vertex_s vertex_t;
/**
 * struct edge_s - Node in the linked list of edges for a given vertex
 * A single vertex can have many edges
 *
 * @dest: Pointer to the connected vertex
 * @next: Pointer to the next edge
 */

typedef struct edge_s
{
	vertex_t *dest;
	struct edge_s *next;
} edge_t;

/**
 * struct vertex_s - Node in the linked list of vertices in the adjacency list
 *
 * @index: Index of the vertex in the adjacency list.
 *   When a new vertex is added, this index becomes the number of vertices
 *   in the adjacency list before it is added.
 *
 * @content: Custom data stored in the vertex (here, a string)
 *
 * @nb_edges: Number of connections with other vertices in the graph
 *
 * @edges: Pointer to the head node of the linked list of edges
 *
 * @next: Pointer to the next vertex in the adjacency linked list
 *   This pointer points to another vertex in the graph, but =>
 *    IT DO NOT STANT FOR AN EDGE BETWEEN TWO VERTICES
 */

struct vertex_s
{
	size_t index;
	char *content;
	size_t nb_edges;
	edge_t *edges;
	struct vertex_s *next;
};

/**
 * struct graph_s - Representation of a graph
 * We use an adjacency linked list to represent our graph
 *
 * All the vertices of the graph are stored in a singly linked list of
 * vertex_t, which 'head' is pointed to by @vertices
 * Each vertex has a pointer @next that points to the next vertex in the list.
 * The @next pointer DOES NOT represent a connection between the two vertices
 * => To represent the connections between vertices, each vertex possesses a singly
 * linked list of edge_t. Each edge struct represents a connection between
 * the vertex and the @dest member of the edge structure. The @next member
 * of an edge points to the next edge in the linked list of edges, for a given
 * vertex.
 *
 * Edges are unidirectional. It means that if we want to create a bidirectional
 * connection between two vertices A and B, we need to create two edges:
 * One in the vertex A's edges linked list, pointing to vertex B;
 * One in the vertex B's edges linked list, pointing to the vertex A.
 *
 * @nb_vertices: Number of vertices in our graph
 * @vertices: Pointer to the head node of our adjacency linked list
 */

typedef struct graph_s
{
	size_t nb_vertices;
	vertex_t *vertices;
} graph_t;

/* After all these structs, a bit of function maybe ? */
graph_t *graph_create(void);
vertex_t *graph_add_vertex(graph_t *graph, const char *str);

/* display the graph for being happy and compare Intranet output */
void graph_display(const graph_t *graph);


#endif /* __HGRAPHS__*/
