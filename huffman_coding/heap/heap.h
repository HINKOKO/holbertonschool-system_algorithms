#ifndef __HEAP__
#define __HEAP__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * struct binary_tree_node_s - Binary tree node data structure
 *
 * @data: Data stored in a node
 * @left: Pointer to left child
 * @right: Pointer to right child
 * @parent: Pointer to parent node
 */

typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} binary_tree_node_t;

/**
 * struct heap_s - Heap data structure
 *
 * @size: Size of the Heap (number of nodes)
 * @data_cmp: Function to compare two nodes data
 * @root: Pointer to the root node of the heap
 */

typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	binary_tree_node_t *root;
} heap_t;

/* Functions prototypes */
heap_t *heap_create(int (*data_cmp)(void *, void *));
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);
binary_tree_node_t *heap_insert(heap_t *heap, void *data);
char *convert(size_t heapsize, size_t base);



#endif /* __HEAP__ */
