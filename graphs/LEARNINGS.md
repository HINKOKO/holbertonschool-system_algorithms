# **Learnings about Graphs -- C**

- ### **What is a graph dudes?**

  **Short answer** => A **graph** is a set of nodes - called <i>vertices</i> - and connections - called <i>edges</i>- connecting the different vertices. <br>
  **Graphs** are used to represent **networks.**
  In Computer Science, graph is a **data structure** that is used to represent connections or relationships between objects.

- ### **What are vertices and edges**

  The **vertices** can represent anything from cities in a map to web-pages in a network, whereas **edges** can represent the relationships between them, such as roads or links.
  The **vertices** can be seen as a collection of points (nodes) connected by "lines" **edges**, where each **vertex** represents a <i>point of interest</i> and each **edge** represents a <i>connection between two points.</i>

- ### **What are the different types of graphs (directed, weighted,...)**

- ### **What are the most common ways used to represent graphs in C**

There are different ways to represent a graph structure in C, the choice is situation-specific, and comes with its pros&cons:

- **Incidence matrix** 
- **Incidence List**

(most commons are)
- **Adjacency matrix**
 A 2D array that represents the graph by storing a '1' at position (i, j), if there's an edge from vertex i to j, and 0 otherwise. <br>

  |            |   A  |  B  |  C  |  D  |
  | -----------| ---- | ----| ----| ----|
  |   A        |  0   |  1  |  1  |  0  |
  |  B         |  1   |  0  |  0  |  1  |
  |  C         |  1   |  0  |  0  |  0  |
  |  D         |  0   |  1  |  1  |  0  |

In this matrix, we learn for example that the graph contains edges from A to B and A to C.

- **Basic Adjacency list**
Adjacency List is a simple way to represent a graph as a list of vertices, where each vertex has a list of its adjacent vertices. An example for an undirected graph with 4 vertices would give the following: <br>

0: 1 3
1: 0 2
2: 1 3
3: 0 2

=> Here vertex 0 is adjacent to vertices 1 and 3 and so on...

- **Holberton_custom_made Adjacency Linked List!**

In the folder of this project, the header file [graphs.h](./graphs.h) declares all the structs necessary for using this architecture. <br>
The main layout/principle remains the same as **Basic Adjacency List** but instead of having an <i>array of vertices</i> we rather use a <i>singly linked list of vertices</i>, by doing so, we will be able to add vertices to the graph, without having to realloc the entire array every time (That's what we learn back in the days of Singly Linked list discovering in our youth).

copyright => <i>Alexandre Gautier</i>




- ### **How to traverse a graph using DFS & BFS**
