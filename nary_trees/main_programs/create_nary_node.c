#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *
 *
 */

typedef struct nary_s
{
	char *content;
	size_t nb_children;
	struct nary_s *parent;
	struct nary_s *children;
	struct nary_s *next;
} nary_t;

nary_t *create_node(char *content, nary_t *parent)
{
	
}
