# **Learnings about Graphs -- C**

- ### **What is a graph dudes?**

  **Short answer** => A **graph** is a set of nodes - called <i>vertices</i> - and connections - called <i>edges</i>- connecting the different vertices. <br>
  **Graphs** are used to represent **networks.**
  In Computer Science, graph is a **data structure** that is used to represent connections or relationships between objects.

- ### **What are vertices and edges**

  The **vertices** can represent anything from cities in a map to web-pages in a network, whereas **edges** can represent the relationships between them, such as roads or links.
  The **vertices** can be seen as a collection of points (nodes) connected by "lines" **edges**, where each **vertex** represents a <i>point of interest</i> and each **edge** represents a <i>connection between two points.</i>

  #### <i><strong>Concerning <s>Hobbits</s> Edges</strong></i> <br>

  Edges can be **directed** or **undirected**, we represent an edge as a pair E = (u, v) u and v being its both endpoints. Directed is like a one-way street and undirected is just like a regular street with double-way circulation traffic. <br>
  This leads us to the notion of directed/undirected Graphs...

- ### **What are the different types of graphs (directed, weighted,...)**

**Undirected** => if a graph is labelized 'undirected', it must satisfy the property that all edges are bidirectional (Analogy => bit like a city with absolutely NO One-way street).

**Directed** => directed graphs or 'di-graphs' are graphs which contains hence <i>directed edges</i>, meaning that all the edges have a specific direction
(imagine a hell-city with only one way-streets).

..................................

<h6> Undirected Polymorphism </h6>
We can always re-draw an <i>undirected graph</i> as <i>directed</i> -> for each undirected edge we will have 2 directed edges, but the opposite is false <br>
.................................

**Weighted** => We also can add a 'notion' of "weight" to the edges. Pursuing our analogy of city / roads and Blabla stuff, We can imagine to "weight" some certain roads regarding to their lenghts or periodic traffic jam... to specify that these "edges" are gonna cost us more time or money or anxiety or fish & chips ! USeful to pick the best path to reach destination.

**Unweighted** => a cool graph with all edges having weight == 1 unit. Equality, fraternity, peace.

- ### **What are the most common ways used to represent graphs in C**

There are different ways to represent a graph structure in C, the choice is situation-specific, and comes with its pros&cons, here are two standards methods:

- **Adjacency matrix**
  A 2D array that represents the graph by storing a '1' at position (i, j), if there's an edge from vertex i to j, and 0 otherwise. <br>

  |     | A   | B   | C   | D   |
  | --- | --- | --- | --- | --- |
  | A   | 0   | 1   | 1   | 0   |
  | B   | 1   | 0   | 0   | 1   |
  | C   | 1   | 0   | 0   | 0   |
  | D   | 0   | 1   | 1   | 0   |

In this matrix, we learn for example that the graph contains edges from A to B and A to C.

- **Basic Adjacency list**
  Adjacency List is a simple way to represent a graph as a list of vertices, where each vertex has a list of its adjacent vertices. An example for an undirected graph with 4 vertices would give the following: <br>

A: B D
B: A C
C: B D
D: A C

=> Here vertex A is adjacent to vertices B and D and so on...

```
         -----       -----
        |  B  |-----|  C  |
       / -----     / -----
      /           /
-----/           /
| A |           /
-----\         /
      \  -----/
       \|  D  |
         -----

```

- **Holberton_custom_made Adjacency Linked List!**

In the folder of this project, the header file [graphs.h](./graphs.h) declares all the structs necessary for using this architecture. <br>
The main layout/principle remains the same as **Basic Adjacency List** but instead of having an <i>array of vertices</i> we rather use a <i>singly linked list of vertices</i>, by doing so, we will be able to add vertices to the graph, without having to realloc the entire array every time (That's what we learn back in the days of Singly Linked list discovering in our youth).

copyright => <i>Alexandre Gautier</i>

- ### **How to traverse a graph using DFS & BFS**

Coming soon babies....we will visit all nodes in the graph 🚀

- #### **DFS - Depth First Search Algorithm**

Depth First Search or Depth First Traversal - "Traversal" means visiting all the vertices of a graph - is a recursive algorithm for searching all vertices & edges in a graph. In [Task 4](./4-depth_first_traverse.c), the purpose is to retrieve the <i>biggest vertex depth</i> we're basically looking for the biggest vertex depth, how deep can we go at max starting with a pointer to a graph. <br>
<br>
Time Complexity of **DFS** is represented as **0(|V| + |E|)** where **V** is the number of vertex, **E** the number of edges.<br>
Space Complexity of this algorithm is **O(V)** <br>
<br>
The main trick is to keep track of each vertex we visit and mark them as <i>visited</i> we also record the deth as we can go deeper along the virgin vertex (<i>not visited yet I mean</i>) and return the max_depth we found at the end.

<strong><u>Applications of DFS:</u></strong>

- Finding the Path
- Detecting cycle in a graph
- Finding the strongly connected components of a graph
- Test if it is a bipartite graph

- #### **BFS - Breadth First Search Algorithm**

Breadth-First Search , as the name suggests, search "wiiiiide" , whereas **DFS** is searching "deeeep". We explore all the "neighborings" nodes rather than looking to go as deep as we can right away, we go "layer-by-layer" through the graph, analyzing the vertices directly connected to the vertex we are starting from.<br>
We fully explore edges out of the most recently discovered node that <i>still has unexplored edges leaving it</i> <br>
<br>
**[Standford lecture extract]**
" **Breadth First Search** expands the frontier between discovered and undiscovered nodes uniformly accross the breadth of the frontier, discovering all nodes at a distance <i>k</i> from the source node before nodes at distance <i>k + 1</i> " <br>
<br>
There again, we keep track of vertex visited and mark them while avoiding cycles. <br>
Note also the use of a **queue data structure** to store the vertices, we operates on the **FIFO** principle, so the node's neighbors will be viewed in the order in which it inserts them in the node.
The time complexity is there again represented as **O(V + E)**, with space complexity of **O(V)** too.
The pseudo-code shows the principle used:

```
BFS (Graph, startNode)
  create an empty queue Q
  push startNode into Q
  mark startNode as 'visited'
  while Q is not empty:
    currentNode = pop from Q
    visit currentNode //Process it, print it, pointer to (void)(*action) in this repo
    for each neighborNode of currentNode:
      if neighborNode is not visited:
        mark it as visited
        enqueue neighborNode into Q
```

<strong><u>Applications of BFS:</u></strong>

- Build index by search index
- For GPS navigation
- Path finding algorithms
- In the "Ford-Fulkerson" algorithm to find maximum flow in a network
- In a peer-to-peer network, BFS can be used as traversal method to find all the **neighboring nodes**. <br>
  Most torrent clients, employ this process to find "seeds" and "peers" in the network
- Cycle detection in undirected graph
- Minimum spanning tree
