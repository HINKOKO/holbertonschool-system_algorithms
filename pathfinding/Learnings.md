# **General Learnings from the project**

- ## **What is Pathfinding**

Pathfinding algorithms deal with the problem of finding a 'path' from a source to a target point, avoiding obstacles and minimizing the costs (time, resources...). This a common programming challenge. Mainly applied to navigation or games, it is actually applied to a wide range of real-life problems.
<br>
At its core, Pathfinding method look into a **graph**, starting at one vertex "start", and explores adjacent vertices until the destination vertex is reached, of course with the intent to find the shortest or "cheapest" path ( in case of **weighted-graph** => to understand that "weight" concept, we can picture a road networks, and each road is assigned a "weight", related to its traffic jam, works on the road or accident... lighter weight are generally assigned to big highways).

- ## **What are the most common applications of Pathfinding**

We find pathfinding problems and applications in those fields:

- GPS/ Navigation, Finding best path between physical locations, the most common usage. Web mapping tools (Google Maps) uses the shortest path algorithm.
- Video Games
- Finding a path for a Robot on Mars (really yeah)
- Market of automated taxicars/buses
- Automated Drones delivering goods.
- Social networks, for finding the degrees of "separation" between a potential new relation.
- Routing tables

- ## **What is 'backtracking', and why you should never use it**

**BAcktracking**... the name suggests itself "taking a step back", or "tracing the route back" upto a particular checkpoint from where you can go ahead again, take another path to your desired destination. Have you already played in a maze ? What do you do when you"re in a dead-end ? you backtrack upto a previous point where another choice of path was possible.... Yeah , you perfom a **backtrack**.
<br>
Applied to programming, it has been the following characteristics:
<br>

- Backtracking is the <i> refinement method of Brute Force</i> it means it finds the number of sub-solutions and each may have number of sub-divisions, and solution chosen for exactly one.

- Backtracking is <i>recursive</i> by nature

- According to Wikipedia: <br>
  "Backtracking is a general algorithm for solving some computational problems, notably constraints ones, that **incrementally builds candidates to the solution and abandon's candidate's (backtracks) as soon as it determines that the candidate cannot be anymore part of the solution.** <br>
  <br>
  Backtracking is like "exhausting all possibilities", so a lot of computations... <br>
  It can be a good way for hard hard problems to which we do not know more efficient solutions, but for 'every day' problems, other techniques are much more efficients.

### **general methodology**

- view picking a solution as a sequence of **choices**
- For each choice, consider every option **recursively**
- Return the best solution found

Even though the methodology seems proper and neat, and even if you take a lot of care implementing your backtracking algorithm, it will still probably take exponential time rather than polynomial time ( => those famous O(log(n) so much appreciated that we look forward to)). <br>
**Backtracking remains a less efficient, memory and time consuming approach by nature.**
<br>

## **What is Dijkstra's Algorithm (and what is its main weakness)**

A bit of History ! this algorithm was created by **Dr Edsger W.Dijkstra**, is the algorithm as complicated as the pronounciation and spelling of the inventor's name ? Thankfully nope. <br>
Okay, anyway he was a brilliant computer scientist and programmer. <br>
Our dutch-man invented this in 20 min, on a cafe terrace, without any pencils or papers, and without those tools, he was almost forced to avoid all avoidable complexities. Maybe the reason of its success! <br>

### **Basics**

Dijkstra's algorithm <i>original</i> find the shortest path between two given nodes in a graph ( which may represent e.g. road networks). <br>
But sometimes you may encounter a <i>variant</i> which fixes single node as variant and find shortest paths from the source to all other nodes in the graph, (producing a **shortest-path tree**).<br>

=> The algorithm begins with a start node, and open a "set" of candidates nodes, that is to say nodes that are going to be part of the final shortest/cheapest-path. <br>
At each step, we examine the node with the lowest distance from the start, that examined node is labelled "visited", and all nodes adjacent to it are added to the open set, if they have not been already examined. Process repeat until the destination node is found. Since the lowest distance are examined first, the first time the destination is found, the path to it will be the **shortest/cheapest** path ! <br>

**However** Dijktras can only deal with **positive weighted graphs**, it always assumes that all edges will be positively-weighted, well otherwise it may still give you an output, but not an accurate one... <br>
Another Weakness is that it does not work with graphs with cycles, and may get stuck in infinite loop. <br>
A perfect example of that Dijkstra's weakness is the **2-main.c** built on purpose of showing a weak spot, Watch carefully the code of that main, that start is A, end is B, with a mega weight applied, and forcefully avoided at first ! Its checks all the others before discovering that ending point is right there, my neighbor, you were there ! huhuhu !!!

```
#include <stdlib.h>
#include <stdio.h>

#include "pathfinding.h"

/**
 * main - Another example to demonstrate the weakness of Dijkstra's algorithm
 * In fact, Dijkstra's algorithm will always choose the shortest path from
 * the starting vertex.
 * In this example, the target vertex is just the neighbour of the starting
 * vertex, but the distance between them is very big. Dijkstra's algorithm will
 * then go through all the vertices, to finally fall back to the target vertex.
 *
 * Return: Either EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    graph_t *graph;
    vertex_t *start, *target;
    queue_t *path;

    graph = graph_create();
    start = graph_add_vertex(graph, "A", 0, 0);
    target = graph_add_vertex(graph, "B", 0, 0);
    graph_add_vertex(graph, "C", 0, 0);
    graph_add_vertex(graph, "D", 0, 0);
    graph_add_vertex(graph, "E", 0, 0);
    graph_add_vertex(graph, "F", 0, 0);
    graph_add_vertex(graph, "G", 0, 0);
    graph_add_vertex(graph, "H", 0, 0);
    graph_add_vertex(graph, "I", 0, 0);
    graph_add_vertex(graph, "J", 0, 0);
    graph_add_vertex(graph, "K", 0, 0);
    graph_add_vertex(graph, "L", 0, 0);
    graph_add_vertex(graph, "M", 0, 0);
    graph_add_vertex(graph, "N", 0, 0);
    graph_add_vertex(graph, "O", 0, 0);

    graph_add_edge(graph, "A", "B", 1000, BIDIRECTIONAL);
    graph_add_edge(graph, "A", "C", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "C", "D", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "D", "E", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "E", "F", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "F", "G", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "G", "H", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "H", "I", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "I", "J", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "J", "K", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "K", "L", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "L", "M", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "M", "N", 10, BIDIRECTIONAL);
    graph_add_edge(graph, "N", "O", 10, BIDIRECTIONAL);

    path = dijkstra_graph(graph, start, target);
    if (!path)
    {
        fprintf(stderr, "Failed to retrieve path\n");
        return (EXIT_FAILURE);
    }

    print_free_path(path);
    graph_delete(graph);

    return (EXIT_SUCCESS);
}
hinkoko@KARAM_SCHUKUM:~/holbertonschool-system_algorithms/pathfinding$  gcc -o 2-dijkstra_graph_1 -Wall -Wextra -Werror -pedantic 2-main_1.c 2-dijkstra_graph.c -lqueues -lgraphs
alex@~/pathfinding$ ./2-dijkstra_graph_1
Checking A, distance from A is 0
Checking C, distance from A is 10
Checking D, distance from A is 20
Checking E, distance from A is 30
Checking F, distance from A is 40
Checking G, distance from A is 50
Checking H, distance from A is 60
Checking I, distance from A is 70
Checking J, distance from A is 80
Checking K, distance from A is 90
Checking L, distance from A is 100
Checking M, distance from A is 110
Checking N, distance from A is 120
Checking O, distance from A is 130
Checking B, distance from A is 1000
Path found:
 A
 B

```

### **Major weaknesses**

- It follows the "Blind search", so wastes time to find the desired output

- Negatives edges values are not allowed !

- We need to "record" or keep track of vertices we have visited
