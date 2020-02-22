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
    // img_fillrect(c2, x, y, rad, rad);
    double xx[] = {100,20,30,10};
    double yy[] = {100,20,30,10};
    // img_fillconvex(c2, 3, xx, yy);
    // filltriangle(200, 100, 300, 100, 250, 200, 200, 100, 250, 0.5)
    img_filltriangle(c2, 200, 100, 220, 100, 210, 110);
    img_write();
  }
}