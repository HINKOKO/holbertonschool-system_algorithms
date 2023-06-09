# **Red Black Tree** :tree:

## **What is a Red-Black tree**

==> A Red-Black Tree is a **binary search tree**, that maintains balanced properties to ensure efficient operations - insertion, deletion, and searching.
Developped by <i>Rudolf Bayer</i> in 1972, later redefined by <i>Leonidas J.Guibas</i> and <i>Robert Sedgewick</i>

So what is that **Red** and **Black** mysterious properties ??
In such a Red-Black tree, each node is labeled with either Red or Black color, which helps maintains the balance of the tree.

A Red-Black tree follows these 5 invariant rules:

- Every node is either Red || Black
- The root node is always Black
- Every leaf node (null or sentinel node) is Black
- If a node is Red, both of its childrens are Black
- Every path from the root node to a NULL node contains the same number of black nodes
