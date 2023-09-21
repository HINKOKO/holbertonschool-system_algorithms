# **C - Pathfinding**

<quote>Getting lost along your path is a part of finding the path you are meant to be on</quote><br>
=> This happened a LOT during the exercises in this folder 😆

**Pathfinding** in computer science : fundamental technique used to find shortest or more "efficient" , the "cheaper" path between two points, for example in a network or a (weighted) graph. <br>
At first, we play with **recursive-backtracking** ("pléonasme" in French)to demonstrate that backtracking a Graph can take a relatively high amount of computation, even if the solution is "close" so to speak.

## **Tasks**

**0. Backtracking - Array**

<i>Write a function that searches for the first path from a starting point to a target point within a two-dimensional array.</i>

Prototype: queue_t *backtracking_array(char \*\*map, int rows, int cols, point_t const *start, point_t const \*target);

- map is the pointer to a read-only two-dimensional array
- A 0 represents a walkable cell
- A 1 represents a blocked cell
- rows and cols are respectively the number of rows and columns of map
- start stores the coordinates of the starting point
- target stores the coordinates of the target point
- Your function must return a queue, in which each node is a point in the path from start to target (See example)
- You’ll have to use recursive backtracking to find the first working path from start to target
- For each visited cell, you’ll have to explore neighbour cells in the following order:
  RIGHT, BOTTOM, LEFT, TOP

**1. Backtracking - Graph**

<i>Write a function that searches for the first path from a starting point to a target point in a graph.</i>

Prototype: queue_t *backtracking_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);

- graph is a pointer to the graph to go through
- start is a pointer to the starting vertex
- target is a pointer to the target vertex
- Your function must return a queue, in which each node is a char \* corresponding to a vertex, forming a path from start to target.
- You’ll have to use recursive backtracking to find the first working path from start to target
- You’ll have to print each visited vertex.

## **General LEarnings**

- [What is Pathfinding](./Learnings.md#what-is-pathfinding)
- [What are the most common applications of Pathfinding](./Learnings.md#what-are-the-most-common-applications-of-pathfinding)
- [What is 'backtracking', and why you should never use it](./Learnings.md#what-is-backtracking-and-why-you-should-never-use-it)
- [What is Dijkstra's Algorithm, and what is its main weakness](./Learnings.md#what-is-dijkstras-algorithm-and-what-is-its-main-weakness)
- [What is a Star ALgorithm, and how is it better than Dijkstra's](./Learnings.md)
