/* Jaime Arana-Rochel, aranarochel */
/* CS152, Winter 2013 */
/* Homework 6 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

matrix *matrix_zero(int n_rows, int n_cols)
{
  int i;
  matrix *mat = (matrix*)malloc(sizeof(matrix));
  float *ents = (float*)malloc(n_rows*n_cols*sizeof(float));
  mat->n_rows = n_rows;
  mat->n_cols = n_cols;
  
  for(i = 0; i < n_rows*n_cols; i++) {
    ents[i] = 0.0;
  }
  mat->entries = ents;
  return mat;
}


float matrix_read(matrix *m, int i, int j)
{
  if(i > m->n_rows) {
    fprintf(stderr,
	    "error matrix_read:row %i not in matrix\n",i);
    exit(1);
  }
  if(j > m->n_cols) {
    fprintf(stderr,
            "error matrix_read:column %i not in matrix\n",j);
    exit(1);
  }
  
  i = i - 1;
  j = j - 1;
  // finds the array index according to column and row
  int index = m->n_cols * i + j;
  return m->entries[index];
}


void matrix_write(matrix *m, int i, int j, float x)
{
  if(i > m->n_rows) {
    fprintf(stderr,
            "error matrix_read:row %i not in matrix\n",i);
    exit(1);
  }
  if(j > m->n_cols) {
    fprintf(stderr,
            "error matrix_read:column %i not in matrix\n",j);
    exit(1);
  }
  
  i = i - 1;
  j = j - 1;
  // finds the array index according to column and row
  int index = m->n_cols * i + j;
  m->entries[index] = x;
  return;
}


matrix *matrix_build(int n_rows, int n_cols, float(*f)(int,int))
{
  int n,m;
  int i;
  matrix *mat = (matrix*)malloc(sizeof(matrix));
  float *ents = (float*)malloc(n_rows*n_cols*sizeof(float));
  mat->n_rows = n_rows;
  mat->n_cols = n_cols;

  // initializes matrix entries
  for(i = 0; i < n_rows*n_cols; i++) {
    ents[i] = 0.0;
  }
  mat->entries = ents;

  // applies function to matrix
  for(n = 0; n < n_rows; n++) {
    for(m = 0; m < n_cols; m++) {
      matrix_write(mat,n+1,m+1,(*f)(n+1,m+1));
    }
  }
  return mat;
}


matrix *matrix_ident(int dim)
{
  int n,m;
  int i;
  matrix *mat = (matrix*)malloc(sizeof(matrix));
  float *ents = (float*)malloc(dim*dim*sizeof(float));
  mat->n_rows = dim;
  mat->n_cols = dim;

  // initializes matrix entries
  for(i = 0; i < dim*dim; i++) {
    ents[i] = 0.0;
  }
  mat->entries = ents;

  // builds identity matrix
  for(n = 0; n < dim; n++) {
    for(m = 0; m < dim; m++) {
      if(m == n) {
	matrix_write(mat,n+1,m+1,1.0);
      } else {
	matrix_write(mat,n+1,m+1,0.0);
      }
    }
  }
  return mat;
}


matrix *matrix_add(matrix *m, matrix *n)
{
  if(m->n_rows != n->n_rows || m->n_cols != n->n_cols) {
    fprintf(stderr,"error matrix_add: matrices are not the same dimensions\n");
    exit(1);
  }

  int i;
  matrix *mat = (matrix*)malloc(sizeof(matrix));
  float *ents = (float*)malloc(m->n_rows*m->n_cols*sizeof(float));

  for(i = 0; i < m->n_rows*m->n_cols; i++) {
    ents[i] = m->entries[i] + n->entries[i];
  }

  mat->n_rows = m->n_rows;
  mat->n_cols = m->n_cols;
  mat->entries = ents;
  return mat;
}


matrix *matrix_mult(matrix *m, matrix *n)
{
  int i,j,k,l;
  float result = 0.0;

  if(m->n_cols != n->n_rows) {
    fprintf(stderr,
	    "error matrix_mult:dimensions of matrices does not allow for mult");
    exit(1);
  }

  matrix *mat = (matrix*)malloc(sizeof(matrix));
  float *ents = (float*)malloc(m->n_rows*n->n_cols*sizeof(float));
  mat->n_rows = m->n_rows;
  mat->n_cols = n->n_cols;

  // initializes matrix entries
  for(i = 0; i < m->n_rows*n->n_cols; i++) {
    ents[i] = 0.0;
  }
  mat->entries = ents;
  
  // calculates matrix mult result
  for(j = 0; j < m->n_rows; j++) {
    for(k = 0; k < n->n_cols; k++) {
      for(l = 0; l < n->n_rows; l++) {
	result = result + matrix_read(m,j+1,l+1)*matrix_read(n,l+1,k+1);
      }
      matrix_write(mat,j+1,k+1,result);
      result = 0.0;
    }
  }
  return mat;
}


matrix *matrix_transpose(matrix *m)
{
  int i,j,k;
  float transpose;
  matrix *mat = (matrix*)malloc(sizeof(matrix));
  float *ents = (float*)malloc(m->n_rows*m->n_cols*sizeof(float));
  mat->n_rows = m->n_cols;
  mat->n_cols = m->n_rows;

  // initializes matrix entries
  for(i = 0; i < m->n_rows*m->n_cols; i++) {
    ents[i] = 0.0;
  }
  mat->entries = ents;
  
  // transposition process
  for(j = 0; j < m->n_rows; j++) {
    for(k = 0; k < m->n_cols; k++) {
      transpose = matrix_read(m,j+1,k+1);
      matrix_write(mat,k+1,j+1,transpose);
    }
  }
  return mat;
}


void matrix_show(matrix *m)
{
  int i,j;

  for(i = 0; i < m->n_rows; i++) {
    putchar('|');
    for(j = 0; j < m->n_cols; j++) {
      printf(" %.1f ",matrix_read(m,i+1,j+1));
    }
    putchar('|');
    putchar('\n');
  }
}


void matrix_free(matrix *m)
{
  free(m->entries);
  free(m);
  return;
}
  

int main()
{
  return 0;
}
  
