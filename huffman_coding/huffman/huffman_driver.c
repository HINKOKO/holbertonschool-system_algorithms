#include "../huffman.h"
#include "../heap/heap.h"

#include <unistd.h>

#define NUM_CHARS 256

/* tree node, heap node */
typedef struct _treenode treenode;
struct _treenode
{
	int freq;		  /* frequency, what determines priority in the heap */
	unsigned char ch; /* character , if any */
	treenode *left, *right;
};

/* priority queue implemented as a binary heap */
typedef struct _pq
{
	int heap_size;
	treenode *A[NUM_CHARS];
} PQ;

/* create empty queue */
void create_pq(PQ *p)
{
	p->heap_size = 0;
}

int parent(int i)
{
	return (i - 1) / 2;
}

int left(int i)
{
	return (2 * i + 1);
}

int right(int i)
{
	return (2 * i + 2);
}

/* makes the subheap with root i into a heap, assuming left(i) and right(i) are heaps */
void heapify(PQ *p, int i)
{
	int l, r, smallest;
	treenode *t;

	l = left(i);
	r = right(i);

	/* find the smallest of parent, left, and right*/
	if (l < p->heap_size && p->A[l]->freq < p->A[i]->freq)
		smallest = l;
	else
		smallest = i;
	if (r < p->heap_size && p->A[r]->freq < p->A[smallest]->freq)
		smallest = r;

	/* swap parent with smallest if needed */
	if (smallest != i)
	{
		t = p->A[i];
		p->A[i] = p->A[smallest];
		p->A[smallest] = t;
		heapify(p, smallest);
	}
}

/* insert element into prior queue*/
void insert_pq(PQ *p, treenode *r)
{
	int i;

	p->heap_size++;
	i = p->heap_size - 1;
	/* we'd like to place r at the end of array */
	/* but this might violate heap property */
	/* we'll start at the end and work our way up */
	while ((i > 0) && (p->A[parent(i)]->freq > r->freq))
	{
		p->A[i] = p->A[parent(i)];
		i = parent(i);
	}
	p->A[i] = r;
}

/* remove elment at head of the queue (i.e. with mini frequencies )*/
treenode *extract_min_pq(PQ *p)
{
	treenode *r;

	if (p->heap_size == 0)
	{
		printf("heap overflow\n");
		exit(1);
	}
	r = p->A[0];
	/* take the last and stick it in the root (just like heapsort)*/
	p->A[0] = p->A[p->heap_size - 1];
	/* one less in the pqueue*/
	p->heap_size--;
	/* left and right are a heap, make the root a heap*/
	heapify(p, 0);
	return (r);
}

/**
 * get_frequencies - computes frequencies for each character
 *
 */

unsigned int get_frequencies(FILE *f, unsigned int *v)
{
	int r, n;
	/* n count character */
	for (n = 0;; n++)
	{
		/* fgetc() gets an unsgined char, converts to int */
		r = fgetc(f);
		/* no more ? out of loop */
		if (feof(f))
			break;
		v[r]++;
	}
	return (n);
}

/**
 * build_huffman - builds the huffman tree
 * from frequencies in freq[] (Huffman Algorithm)
 */

treenode *build_huffman(unsigned int freqs[])
{
	int i, n;
	treenode *x, *y, *z;
	PQ p;
	/* make empty queue */
	create_pq(&p);

	/* for each character, make a heap/tree node with its value */
	/* and its frequency */
	for (i = 0; i < NUM_CHARS; i++)
	{
		x = malloc(sizeof(treenode));
		/* its a leaft of the huffman tree */
		x->left = x->right = NULL;
		x->freq = freqs[i];
		x->ch = (char)i;
		/* put this node into the heap */
		insert_pq(&p, x);
	}
	/* at this point, the heap is a "forest" of singleton trees */

	n = p.heap_size - 1; /*  heap_size isn't loop invariant ! */

	/**
	 * if we insert two-things and remove one each time
	 * at the end of heap_size - 1 iterations, there will be
	 * one tree left in the heap
	 */
	for (i = 0; i < n; i++)
	{
		/* make a new node z from the two least frequent x and y*/
		z = malloc(sizeof(treenode));
		x = extract_min_pq(&p);
		y = extract_min_pq(&p);
		z->left = x;
		z->right = y;
		/* z's frquency is the sum !*/
		z->freq = x->freq + y->freq;
		/* put this back into the queue */
		insert_pq(&p, z);
	}
	/* return the only thing left in the queue, the whole Huffman tree */
	return extract_min_pq(&p);
}

/* traverse the Huffman Tree, building up the codes in codes[] */
/* *codes[] array of codes */
void traverse(treenode *r, int level, char code_so_far[], char *codes[])
{
	/* if we're at the leaf node */
	if (!r->left && !r->right)
	{
		/* put in a Null terminator */
		code_so_far[level] = 0;
		/* make a copy and put it in the array */
		codes[r->ch] = strdup(code_so_far);
	}
	else
	{
		/* not a leaf node. go left with bit 0*/
		code_so_far[level] = '0';
		traverse(r->left, level + 1, code_so_far, codes);
		/* go right with bit 1*/
		code_so_far[level] = '1';
		traverse(r->right, level + 1, code_so_far, codes);
	}
}

/* global variables , necessary evil */
int nbits, current_byte, nbytes;

/* output a single bit to an open file */
void bitout(FILE *f, char b)
{
	/* shift current byte left one */
	current_byte <<= 1;
	/* put a one on the end of this byte if b is '1' */
	if (b == '1')
		current_byte |= 1;
	/* one more bit */
	nbits++;
	/* enough bits ? write out the byte */
	if (nbits == 8)
	{
		fputc(current_byte, f);
		nbytes++;
		nbits = 0;
		current_byte = 0;
	}
}

/**
 * encode_file - using the codes in codes[]
 * encode the file in infile, writing result in outfile
 */

void encode_file(FILE *infile, FILE *outfile, char *codes[])
{
	unsigned char ch;
	char *s;

	/* init global for bitouts */
	current_byte = 0;
	nbits = 0;
	nbytes = 0;
	/* continue till end of file */
	for (;;)
	{
		/* get a char */
		ch = fgetc(infile);
		if (feof(infile))
			break;
		/* put corresponding bitstring in outfile */
		for (s = codes[ch]; *s; s++)
			bitout(outfile, *s);
	}
	/* finish off the last byte */
	while (nbits)
		bitout(outfile, '0');
}

/* int access(const char *pathname, int mode); */
/* F_OK mode check for existence of the file */

int check(int argc, char *argv[])
{
	if (argc != 4 || strlen(argv[1]) != 1 ||
		!strcmp(argv[1], "c"))
		return (fprintf(stderr, "Usage: huffman <mode> <filename> <out_filename>\n"), EXIT_FAILURE);

	if (access(argv[2], F_OK) == -1)
		return (fprintf(stderr, "No such file: %s\n", argv[2]), EXIT_FAILURE);

	if (access(argv[3], F_OK) != -1)
		return (fprintf(stderr, "File already exists: %s\n", argv[3]), EXIT_FAILURE);

	return (*argv[1] == 'c' ? 1 : -98);
}

int main(int argc, char **argv)
{
	FILE *f, *g;
	treenode *r;				   /* root of Huffman tree */
	unsigned int n;				   /* number of bytes in file to compress */
	unsigned int freqs[NUM_CHARS]; /* frequency of each char */

	char *codes[NUM_CHARS]; /* array of codes, one per char */
	char code[NUM_CHARS];	/* a place to hold one code */
	char fname[100];		/* what to call output file */

	int mode = check(argc, argv);
	if (mode < 0)
		exit(EXIT_FAILURE);

	/* set frequencies to 0 */
	memset(freqs, 0, sizeof(freqs));
	/* open command line argument file */
	f = fopen(argv[2], "r");
	if (!f)
	{
		perror(argv[2]);
		exit(1);
	}
	/* compute frequencies from this file */
	n = get_frequencies(f, freqs);
	fclose(f);
	/* make huffman tree*/
	r = build_huffman(freqs);
	/* traverse tree, filling codes[] with the codes */
	traverse(r, 0, code, codes);
	/* name the output file something, uh argv[3] nope ? */
	sprintf(fname, "%s", argv[3]);
	g = fopen(fname, "w");
	if (!g)
	{
		perror(fname);
		exit(1);
	}

	/*write frequencies to the file */
	fwrite(freqs, NUM_CHARS, sizeof(int), g);
	/* write number of characters to the file as binary int */
	fwrite(&n, 1, sizeof(int), g);
	/* open inut file again*/
	f = fopen(argv[2], "r");
	if (!f)
	{
		perror(argv[2]);
		exit(1);
	}

	/* encode f to g with codes[] */
	encode_file(f, g, codes);
	fclose(f);
	fclose(g);
	/* brag */
	exit(0);
}
