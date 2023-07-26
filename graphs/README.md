# **C-Graphs**

## **[Learnings](./LEARNINGS.md)📕**

- What is a graph
- What are vertices and edges
- What are the different types of graphs (directed, weighted, …)
- What are the most common ways used to represent graphs in C
- How to traverse a graph using DFS and BFS

### **Task - 0 => Create graph**

<i>Write a function that allocates memory to store a graph_t structure, and initializes its content.</i>

Prototype: graph_t \*graph_create(void);
Your function must return a pointer to the allocated structure, or NULL on failure

```
Hinkoko@~/graphs$ cat 0-main.c
#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    graph_t *graph;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    printf("Successfully created graph\n");

    return (EXIT_SUCCESS);
}
Hinkoko@~/graphs$ gcc -Wall -Wextra -Werror -pedantic 0-main.c 0-graph_create.c -o 0-graph_create
Hinkoko@~/graphs$ ./0-graph_create
Successfully created graph
```
