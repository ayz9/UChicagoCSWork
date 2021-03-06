/* Jaime Arana-Rochel, aranarochel */
/* CS152, Winter 2013 */
/* Lab 8 */
#include <stdlib.h>
#include <stdio.h>

#include "vcard.h"
#include "bst.h"

void bst_todo(char *s)
{
  fprintf(stderr, "TODO[bst]: %s\n", s);
  exit(1);
}

bst *bst_singleton(vcard *c)
{
  bst *singleton = (bst*)malloc(sizeof(bst));
  singleton->c = c;
  singleton->lsub = NULL;
  singleton->rsub = NULL;
  return singleton;
}

bst *bst_insert(bst *t, vcard *c)
{
  if(t == NULL)
    return bst_singleton(c);
  if(strcmp(c->cnet,t->c->cnet) < 0) {
    t->lsub = bst_insert(t->lsub,c);
    return t;
  } else {
    if(strcmp(c->cnet,t->c->cnet) > 0) {
      t->rsub = bst_insert(t->rsub,c);
      return t;
    }
    return t;
  }
}

unsigned int bst_num_entries(bst *t)
{
  if(t == NULL)
    return 0;
  return 1 + bst_num_entries(t->lsub) + bst_num_entries(t->rsub);
}

/* max : int int -> int */
/* return the max of two numbers */
int max(int a, int b)
{
  return (a < b) ? b : a;
}

unsigned int bst_height(bst *t)
{
  if(t == NULL)
    return 0;
  return 1 + max(bst_height(t->lsub),bst_height(t->rsub));
}

vcard *bst_search(bst *t, char *cnet, int *n_comparisons)
{
  if(t == NULL)
    return NULL;
  if(strcmp(cnet,t->c->cnet) == 0) {
    (*n_comparisons)++;
    return t->c;
  } else if(strcmp(cnet,t->c->cnet) < 0) {
    (*n_comparisons)++;
    return bst_search(t->lsub,cnet,n_comparisons);
  } else {
    (*n_comparisons)++;
    return bst_search(t->rsub,cnet,n_comparisons);
  }
}
  

void bst_free(bst *t)
{
  vcard_free(t->c);
  bst_free(t->lsub);
  bst_free(t->rsub);
  free(t->lsub);
  free(t->rsub);
  free(t);
}
