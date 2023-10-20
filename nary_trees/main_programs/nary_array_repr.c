#include <stdio.h>
#include <stdlib.h>

/* get the index of parent node at given index */

int get_parent_idx(int index, int n)
{
	return ((index - 1) / n);
}

/* get index of k-th child of node at given index */
int get_child_idx(int index, int k, int n)
{
	return (n * index + k + 1);
}

int main(void)
{
	int i, k;	   /* array iterators */
	int n = 3;	   /* childrens per node */
	int size = 13; /* size of array (number of nodes) */
	/* memory booking for the array */
	int *arr = (int *)malloc(size * sizeof(int));
	/* Assign values to array */
	for (i = 0; i < size; i++)
		arr[i] = i;
	/* print array */
	for (i = 0; i < size; i++)
		printf("%d\n", arr[i]);
	printf("\n");

	/* Print parent and children for each node ! */
	for (i = 0; i < size; i++)
	{
		printf("Node %d: parent = %d, children = ", arr[i], get_parent_idx(i, n));
		for (k = 0; k < n; k++)
		{
			int child_idx = get_child_idx(i, k, n);
			if (child_idx < size)
				printf("%d ", arr[child_idx]);
		}
		printf("\n");
	}
	free(arr);
	return (0);
}
