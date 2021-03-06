#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "bits.h"
#include "huff.h"


int is_last_char(char c, char *s)
{
  if(c == s[(strlen(s)-1)]) 
    return 1;
  return 0;
}

huff *insert_code(huff *node,char *code,int i,int c)
{
  // if char is last char in code...
  if(i == (strlen(code)-1)) {
    // create leaf and attach to node
    if(code[i] == '0') {
      huff *leaf = huff_singleton((char)c,0);
      node->h.node.lsub = leaf;
    } else if(code[i] == '1') {
      huff *leaf = huff_singleton((char)c,0);
      node->h.node.rsub = leaf;
    }
    // if char is not last char in code...
  } else if(i != (strlen(code)-1)) {
    // if char is '0'...
    if(code[i] == '0') {
      // if lsub of node is not NULL recursively travel through lsub
      if(node->h.node.lsub != NULL) {
	i = i + 1;
	insert_code(node->h.node.lsub,code,i,c);
	// if lsub is NULL create new lsub, attach to node, and recur
      } else if(node->h.node.lsub == NULL) {
	i = i + 1;
	huff *new = huff_single_node(0);
	node->h.node.lsub = new;
	insert_code(node->h.node.lsub,code,i,c);
      }
      // if char is '1'...
    } else if(code[i] == '1') {
      // if rsub is not NULL, recur through rsub
      if(node->h.node.rsub != NULL) {
	i = i + 1;
	insert_code(node->h.node.rsub,code,i,c);
	// if rsub is NULL, create new rsub, attach, and recur
      } else if(node->h.node.rsub == NULL) {
	i = i + 1;
	huff *new = huff_single_node(0);
	node->h.node.rsub = new;
	insert_code(node->h.node.rsub,code,i,c);
      }
    }
  }
  return node;
}

huff *huff_deserialize(char **codes)
{
  huff *start = huff_single_node(0);
  int i;
  int k = 0;
  
  for(i = 0; i < 128; i++) {
    if(codes[i] != NULL) {
      start = insert_code(start,codes[i],k,i);
    }
  }
  return start;
}

void bits_to_txt(huff *h, char *bits, int i)
{
  switch (h->tag) {
  case LEAF:
    putchar(h->h.leaf.c);
    if(is_last_char(bits[i],bits) == 0) {
      i = i + 1;
      bits_to_txt(h,bits,i);
    }
    break;
  case NODE:
    if(bits[i] == '0') {
      i = i + 1;
      bits_to_txt(h->h.node.lsub,bits,i);
    } else {
      i = i + 1;
      bits_to_txt(h->h.node.rsub,bits,i);
    }
    break;
  }
}

