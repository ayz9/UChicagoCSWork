/* Jaime Arana-Rochel, aranarochel */
/* CS152, Winter 2013 */
/* Homework 2 */
#include <stdlib.h>
#include <stdio.h>


/* draw_row : int int char char -> <void> */
/* draws a checkerboard row given a square length,
   squares/row, and two characters */
void draw_row(int len,int sqrs,char c1,char c2)
{
  int a;
  int i;
  int j;
  int k;
  int m;
 
  if(sqrs == 1) {
    for(i = 0; i < len; i++) {
      for(j = 0; j < len; j++) {
	putchar(c1);
      }
      putchar('\n');
    }
  } else if(sqrs % 2 == 0) {   /* case for even number of squares */
    for(a = 0; a < len; a++) {
      for(i = 0; i < (sqrs / 2); i++) {
	for(j = 0; j < len; j++) {
	  putchar(c1);
	}
	for(k = 0; k < len; k++) {
	  putchar(c2);
	}
      }
      putchar('\n');
    }
  } else if(sqrs % 2 != 0) {   /* case for odd number of squares */
    for(a = 0; a < len; a++) {
      for(i = 0; i < (sqrs / 2); i++) {
	for(j = 0; j < len; j++) {
	  putchar(c1);
	}
	for(k = 0; k < len; k++) {
	  putchar(c2);
	}
      }
      for(m = 0; m < len; m++) {
	putchar(c1);
      }
      putchar('\n');
    }
  }
}


/* checker : int int char char -> <void> */
/* draws an nxn ASCII checkerboard given a square length
   squares/row, and two characters */
void checker(int len,int sqrs,char c1,char c2)
{
  int i;

  if(sqrs % 2 == 0) {
    for(i = 0; i < (sqrs / 2); i++) {
      draw_row(len,sqrs,c1,c2);
      draw_row(len,sqrs,c2,c1);
    }
    putchar('\n');
  } else if (sqrs % 2 != 0) {
    for(i = 0; i < (sqrs / 2); i++) {
      draw_row(len,sqrs,c1,c2);
      draw_row(len,sqrs,c2,c1);
    }
    draw_row(len,sqrs,c1,c2);
  }
  putchar('\n');
}



int main(int argc,char *argv[])
{
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  int c = argv[3][0];
  int d = argv[4][0];
  checker(a,b,c,d);
  return 0;
}

