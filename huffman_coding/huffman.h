#ifndef __HUFFMAN__
#define __HUFFMAN__

#include <stdlib.h>
#include <stddef.h>
#include "heap/heap.h"

/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */

typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

/* functions stuff */
symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);

#endif /* __HUFFMAN__ */
