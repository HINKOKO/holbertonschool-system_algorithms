#include "huffman.h"

/**
 * symbol_create - creates a symbol_t data struct
 * Spicy part is coming soon !!!
 * @data: data to be stored
 * @freq: frequency of that data
 * Return: pointer to the created struct, NULL on failure
 */

symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *new = malloc(sizeof(*new));

	if (!new)
		return (NULL);

	new->data = data;
	new->freq = freq;
	return (new);
}
