// goround --- go round in 3D space
#include "img.h"
#include <math.h>
#define PI 3.14159265358979

int main(void) {
  struct color c1 = { 30, 255, 0 };
  struct color c2 = { 255, 0, 0 };
  int i;
  for(i = 0; i < 40; ++i) {
    double sx = sin(2*PI*i/40);
    double cx = cos(2*PI*i/40);
    double rad = 20 - 10*sx;
    double x = 150 + 100*cx;
    double y = 100 + 50*sx;
    img_clear();
    // img_fillcircle(c2, x, y, rad);
    img_fillrect(c2, x, y, rad, rad);
    img_write();
  }
}