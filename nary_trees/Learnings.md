# **General Learnings for this project**

### - [**1. What is a N-ary tree**](1)

A N-ary tree - a.k.a "k-ary" , "k-way" or even "multiway" tree - is a special type of **tree-structure** where each node can have **0 to N** child nodes. In contract, classic binary tree have **at most** 2 child nodes per node.

#### **Types of N-ary trees**<br>

1. A **Full N-ary** tree is when each level has **0 or N childrens**
2. A **complete N-ary** tree is a **full n-ary tree** where each level are at the same depth.

#### **Properties**

--> For an N-ary tree with height **h**, the upper bound for the maximum number of leaves is **N^h** (N to the power of h). <br>
--> The height h of an N-ary tree <u>does not include the root node</u> Hence a tree containing only a root node has a height of 0. <br>
--> The height of a tree is equal to the maximum depth D of any node in the tree.

### - [**2. What are the most common usage of N-ary trees**](2)

N-ary trees are a versatile data structure by nature, suitable for several applications: <br>

#### **File systems representation**

In a file system, dirs and sub-dirs must be kept organized, in a hierarchical data structure. Each directory may contain files and/or sub-dirs. <br>
This situation can be handled and represented as an **N-ary tree**, with each dir as -> Node and sub-dirs and files as -> childrens <br>

#### **Representation of Parse trees**

Compilers and parsers generates **parse-trees** (a.k.a "syntax trees"), N-ary tree are suitable too to handle this situation. Each node then represents a syntactic element in the program , and its childrens represents the sub-elements. <br>
Parse trees have nodes to represent **syntactic elements** such as operators, variables, expressions...<br> and egdes represent **relationships** between these elements.
**Then**, for example, in an arithmetic expression like **a + b \* c**, the parse tree would have the **+** node as the **parent**, with **a** as the left child and <strong>_</strong> as the **right child** The <strong>_</strong> node would have **b** as the **left child** and **c** as the **right child.**

```
           +
		  / \
	     /   \
		a     *
		     / \
			b   c
```

The parse tree properly reflects the **precedence** and **associativity** of the operators in the original expression. Mult has higher precedence, so -> it appears deeper in the tree. And we are very happy.

#### **Organization chart**

Boring example but can be used to represent the "social-levels" of management in a company, each node representing person/position/level, with each 'childs' for peoples or positions linked to it.

#### **Decision tree**

More exciting -> Machine learning and artificial intelligence to model decisions and possible outcomes/consequences. With each node representing a **decision point** and its children representing the **possible outcomes**

#### **Game tree**

To model the possible moves and outcomes in a game, you can use a N-ary tree dude, you'll be just fine. Each node can be then each **possible-moves**, with childrens for **possible counter-moves**

### [**3. How to represent an N-ary tree in C in at least two different ways**](3)

- #### **Using good old struct and pointers**

You can define a **struct** to hold the value/content of the node and a pointer to its children(s). The, you can just use a pointer to this struct to represent the **root** of your N-ary tree, and the kids of each node can be represented using a linked list of pointers to their respective structs. The [nary_trees](./nary_trees.h) file of this folder shows a struct of this kind.

### **4. What is the diameter of an N-ary tree**(4)

Diameter refers to the **longest path between any two nodes in the tree**. It can be defined as the maximum value of the sum of the distances from the <br>
root node to any two nodes in the tree. <br>

In other words (<quote>Please be true, I love you</quote><i>Frank Sinatra</i>), the **diameter** of N-ary tree is the maximum of the distance between <br>
the **root node and the farthest leaf node**, and the distances between the **two farthest leaf nodes** in the tree.

=> Put simply, yeah I will say it again => The **diameter** of an N-ary tree is the length of the longest path between any two nodes in the tree, they must be leaf nodes, This path may or may not pass through the root node.

=> In order to **calculate** it
