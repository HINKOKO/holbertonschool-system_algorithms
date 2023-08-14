# **Learnings**

## **Learnings of project**

- **What is a binary Heap (min & max)**

  A binary-Heap is a specialized binary-tree-based data structure that fullfil the **heap property** => which can be **max** or **min** (The **heap-property** dictates the relationship berween parent and child nodes in the heap). <br>

  Binary Heaps are a common way to implement **priority queues** <br>
  A binary heap, let's say that again, is created as a binary tree but with two additional constraints:

  - **Shape Property**: A binary heap is a <i>complete binary-tree</i>, that is, all levels of the tree, except possibly the last one are fully filled, and, if the last level of tree is not complete, the nodes of that level are filled from left to right

  - **Heap property**: The key stored in each node is either greater than or equal to // or less than or equal to the key's in the node's children. (Either a max or min-heap respectively)

  The Heap is often implemented with an Array. Any binary tree can be stored in an array, but because binary heap is always a <i>complete binary tree</i>, it can be stored compactly, the parent and children of each node can be then found by arithmetic on array indices:
  Let N be the number of elements in the heap, and <i>i</i> an arbitraty (valid) index (between 0 and N - 1), then we can say for a given element <i>a</i> at index <i>i</i>:

  - Left Children at index 2<i>i</i> + 1
  - Right Children at index 2<i>i</i> + 2
  - Parent at index floor((i - 1) / 2)

<img src="./img/HeapArray.png">

- What is a priority queue

- What is a Huffman code

- **Compilation trick (I'm still a baby)**

- Flags -Iheap/ and -I/
  => -Iheap/ => This tells the compiler to include the directory named "heap/" in its research path for header files.
  => -I./ tells the compiler to include the current directory also in its search path for header files

Both of flags used to ensure that compiler finds the necessary header files for our source code, regardless of their relative locations.
