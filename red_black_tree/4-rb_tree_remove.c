#include "rb_trees.h"

/**
 * rb_transplant - replace connections according
 * @tree: double pointer to root node
 * @u: 'before' config node
 * @v: 'after' function config node connexions
 */

void rb_transplant(rb_tree_t **tree, rb_tree_t *u, rb_tree_t *v)
{
	if (!u->parent)
		*tree = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}
/**
 * get_min - return the min of the BST subtree
 * @x: pointer to node from where to start get_min func
 * Return: node with the min value inorder way
 */

rb_tree_t *get_min(rb_tree_t *x)
{
	while (x->left)
		x = x->left;
	return (x);
}

/**
 * rb_delete_fixup - fix colors mess
 * handle all possible sibling config => to be split in separate func
 * @tree: double pointer to root node
 * @x: the node to fix repair service
 */

void rb_delete_fixup(rb_tree_t **tree, rb_tree_t *x)
{
	rb_tree_t *w = NULL;

	while (x != *tree && x->color == BLACK)
	{
		if (x == x->parent->left)
		{
			w = x->parent->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				rbt_left_rotate(tree, x->parent);
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					rbt_right_rotate(tree, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rbt_left_rotate(tree, x->parent);
				x = *tree;
			}
		}
		else
		{
			w = x->parent->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				rbt_right_rotate(tree, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					rbt_left_rotate(tree, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rbt_right_rotate(tree, x->parent);
				x = *tree;
			}
		}
	}
	x->color = BLACK;
}

/**
 * rbt_remove_node - perform the removal of node from rbt
 * and make the connection between branches to keep a tree a tree
 * @tree: double pointer to root node of tree
 * @z: the node to erase
 * VISIT CODESDOPE.COM !!!
 */

void rbt_remove_node(rb_tree_t **tree, rb_tree_t *z)
{
	rb_tree_t *y = z;
	rb_tree_t *x;
	int y_color = y->color;

	if (!z->left)
	{
		x = z->right;
		rb_transplant(tree, z, z->right);
	}
	else if (!z->right)
	{
		x = z->left;
		rb_transplant(tree, z, z->left);
	}
	else
	{
		y = get_min(z->right);
		y_color = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = z;
		else
		{
			rb_transplant(tree, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		rb_transplant(tree, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_color == BLACK)
		rb_delete_fixup(tree, x);
}

/**
 * rb_tree_remove - removes a node from a Reb-Black tree
 * @root: pointer to root node
 * @n: value to search and kill
 * Return: pointer to new root (may change)
 */

rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *cur = root;

	/* find that guy to kick off */
	while (cur)
	{
		if (cur->n == n)
			break;
		else if (cur->n < n)
			cur = cur->left;
		else
			cur = cur->right;
	}
	/* no found return the Return expected */
	if (!cur)
		return (root);
	rbt_remove_node(&root, cur);
	return (root);
}
