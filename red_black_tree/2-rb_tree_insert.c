#include "rb_trees.h"

/**
 * rbt_right_rotate - performs right rotation learnt in AVL project
 * @tree: db pointer to root node
 * @node: the node to flip flap
 */

void rbt_right_rotate(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *flip = NULL;

	flip = node->left;
	node->left = flip->right;
	if (flip->right)
		flip->right->parent = node;
	flip->parent = node->parent;
	if (node->parent == NULL)
	{
		/* to rotating reached the top */
		*tree = flip;
	}
	else if (node == node->parent->left)
		node->parent->left = flip;
	else
		node->parent->right = flip;
	flip->right = node;
	node->parent = flip;
}

/**
 * rbt_left_rotate - performs lef trotation learnt in AVL project
 * @tree: db pointer to root node
 * @node: the node to flip flap
 */

void rbt_left_rotate(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *flip = NULL;

	flip = node->right;
	node->right = flip->left;
	if (flip->left)
		flip->left->parent = node;
	flip->parent = node->parent;
	if (node->parent == NULL)
		*tree = flip;
	else if (node == node->parent->left)
		node->parent->left = flip;
	else
		node->parent->right = flip;
	flip->left = node;
	node->parent = flip;
}

/**
 * rbt_left_fix - performs a "left-fixage" after insertion left aligned
 * and colors mixed up
 * @tree: double pointer to root node
 * @new: the new inserted node to fix
 * Return: pointer to fixed node (the originally inserted)
 */

rb_tree_t *rbt_left_fix(rb_tree_t **tree, rb_tree_t *new)
{
	rb_tree_t *uncle = NULL;

	/* check if uncle is RED => hoho ! */
	uncle = new->parent->parent->left;
	if (uncle && uncle->color == RED)
	{
		new->parent->color = BLACK;
		uncle->color = BLACK;
		new->parent->parent->color = RED;
		/* lift up one floor to check if fix need after recoloration */
		new = new->parent->parent;
	}
	else
	{
		/* else rotation */
		if (new == new->parent->left)
		{
			/* new in 3-left align position */
			/* move new pointer up to prepare rotation to right */
			new = new->parent;
			rbt_right_rotate(tree, new);
		}
		new->parent->color = BLACK;
		new->parent->parent->color = RED;
		rbt_left_rotate(tree, new->parent->parent);
	}
	return (new);
}

/**
 * rbt_right_fix - fix tree when insertion right case
 * @tree: double pointer to root node
 * @new: the new inserted node to fix
 * Return: pointer to fixed node (the originally inserted)
 */

rb_tree_t *rbt_right_fix(rb_tree_t **tree, rb_tree_t *new)
{
	rb_tree_t *uncle = NULL;

	uncle = new->parent->parent->right;
	if (uncle && uncle->color == RED)
	{
		new->parent->color = BLACK;
		uncle->color = BLACK;
		new->parent->parent->color = RED;
		/* lift up to repeat fix if needed */
		new = new->parent->parent;
	}
	else
	{
		if (new == new->parent->right)
		{
			new = new->parent;
			rbt_left_rotate(tree, new);
		}
		/* fix final color first */
		new->parent->color = BLACK;
		new->parent->parent->color = RED;
		/* perform rotation */
		/* new->parent->parent as pivot */
		rbt_right_rotate(tree, new->parent->parent);
	}
	return (new);
}

/**
 * rbt_fix - first fix step to fix the insertion in rbt
 * redirect to fix_left or fix_right
 * @tree: double pointer to root node
 * @new: pointer to new node to fix
 */

void rbt_fix(rb_tree_t **tree, rb_tree_t *new)
{
	while (new->parent && (new->parent->color == RED))
	{
		if (new->parent->parent && (new->parent == new->parent->parent->left))
			new = rbt_right_fix(tree, new);
		else
			new = rbt_left_fix(tree, new);
	}
	/* root at the end should be black */
	(*tree)->color = BLACK;
}

/**
 * rb_tree_insert - performs insertion in a RBT
 * @tree: double pointer to the root node of RBT
 * @value: value to store in new node inserted
 * Return: pointer to the created node, or NULL if failure
 */

rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new = NULL, *cur = NULL, *prev = NULL;

	if (!tree)
		return (NULL);
	/* place cur at root */
	cur = *tree;
	while (cur)
	{
		/* record previous cur position */
		prev = cur;
		if (cur->n == value)
			return (NULL);
		if (value > cur->n)
			cur = cur->right;
		else if (value < cur->n)
			cur = cur->left;
	}
	/* cur is arrived at correct position to insert */
	/* use function 0 to declare a RED node, easier to fix */
	new = rb_tree_node(prev, value, RED);
	if (!new)
		return (NULL);
	if (!prev)
		*tree = new;
	else if (new->n < prev->n)
		prev->left = new;
	else
		prev->right = new;
	rbt_fix(tree, new);
	return (new);
}
