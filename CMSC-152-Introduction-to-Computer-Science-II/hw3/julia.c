/* Jaime Arana-Rochel, aranarochel */
/* CS152, Winter 2013 */
/* Homework 3 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* julia_set : int int double double -> <void> */
/* given an image size, iteration limit, and 
   complex number c, produce a julia set fractal */
void julia_set(int len, int lim, double c_re, double c_im)
{
  int x, y, i;
  double z_re, z_im, z_rei, z_imi;

  printf("P3\n");
  printf("%d %d\n",len,len);
  printf("255\n");

  for(y = 0; y < len; y++) {
    for(x = 0; x < len; x++) {
      if(x == 0 && y == 0) {
	z_re = -2;
	z_im = 2;
      } else {
	z_re = -2 + ((4.0/len) * (double)x);
	z_im = 2 - ((4.0/len) * (double)y);
      }
      for (i = 0; i < lim; i++) {
	z_rei = z_re;
	z_imi = z_im;
	z_re = z_rei * z_rei - z_imi * z_imi + c_re;
	z_im = 2 * z_rei * z_imi + c_im;
      }
      if((z_rei * z_rei + z_imi * z_imi) < 4) {
	printf("0 0 0\n");
      } else {
	printf("255 255 255\n");
      }
    }
  }
}


int main(int argc,char *argv[])
{
  int s = 480;
  int c;
  double c_re, c_im;

  while (--argc > 0 && (*++argv)[0] == '-')
    while (c = *++argv[0])
      switch (c) {
      case 's':
        s = atoi(argv[1]);
	c_re = atof(argv[2]);
	c_im = atof(argv[3]);
        break;
      }

  julia_set(s,13,c_re,c_im);
  return 0;
}

  
