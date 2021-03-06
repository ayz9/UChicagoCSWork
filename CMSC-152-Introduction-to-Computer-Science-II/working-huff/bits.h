#ifndef _BIT_ARRAY_LISTS_H
#define _BIT_ARRAY_LISTS_H

/* This is a data structure to contain
   array lists of "bits", represented here
   as chars '0' and '1' since space is not a concern
   in the present context. 
*/

struct bits {
  int capacity;
  int next;
  char *bits;
};

typedef struct bits bits;

/* Allocate fresh bits struct with given capacity. */
bits *bits_new(unsigned int sz);

void bits_free(bits *a);

void bits_show(bits *a);

/* Write the "bit" b at the next available spot in array a. */
/* On insufficient capacity, fail (this is not expected to be a problem). */
void bits_putlast(char b, bits *a);

/* "Remove" the last bit in the array list. */
/* Implemented simply by decrementing the "next" index. */
void bits_remove_last(bits *a);

#endif /* _BIT_ARRAY_LISTS_H */
