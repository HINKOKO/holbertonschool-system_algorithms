# **General Learnings from the project**

- ## **What is Pathfinding**

Pathfinding algorithms deal with the problem of finding a 'path' from a source to a target point, avoiding obstacles and minimizing the costs (time, resources...). This a common programming challenge. Mainly applied to navigation or games, it is actually applied to a wide range of real-life problems.

- ## **What are the most common applications of Pathfinding**

Haha you 'd like to knwo uh ? uh dude uh ? uhuhuhuhu

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
But sometimes you may encounter a <i>variant</i> which fixes single node as variant and find shortest paths from the source to all other nodes in the graph, (producing a **shortest-path tree**).
