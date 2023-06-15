#ifndef __RBTREES__
#define __RBTREES__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * enum rb_color_e - Possible color of a Red-Black tree
 *
 * @RED: 0 -> Red node
 * @BLACK: 1 -> Black node
 * @DOUBLE_BLACK: Double black node
 */

typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
 * struct rb_tree_s - Red-Black tree node structure
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 * @color: Color of the node (RED or BLACK)
 */

typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;

/* proto functions */

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);
int rb_tree_is_valid(const rb_tree_t *tree);
/* Insertion stuff */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
void rbt_right_rotate(rb_tree_t **tree, rb_tree_t *node);
void rbt_left_rotate(rb_tree_t **tree, rb_tree_t *node);
rb_tree_t *rbt_left_fix(rb_tree_t **tree, rb_tree_t *new);
rb_tree_t *rbt_right_fix(rb_tree_t **tree, rb_tree_t *new);
void rbt_fix(rb_tree_t **tree, rb_tree_t *new);
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
/*****************************************************/
/** End of insertion fixage **/

/* Task 3 easy peasy */
rb_tree_t *array_to_rb_tree(int *array, size_t size);

/* about deletion NOT EASY */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);
void rbt_remove_node(rb_tree_t **tree, rb_tree_t *z);
void rb_delete_fixup(rb_tree_t **tree, rb_tree_t *x);
rb_tree_t *get_min(rb_tree_t *x);
void rb_transplant(rb_tree_t **tree, rb_tree_t *u, rb_tree_t *v);

#endif /* __RBTREES__ */
