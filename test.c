#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include <math.h>

#define PI 3.14159265358979

int main(void)
{
    int i = 0;
    for (i = 0; i < 21; ++i)
    {
        printf("i:  %d\n", i);
        double sx = sin(2 * PI * i / 40);
        printf("sx: %lf\n", sx);
        double cx = cos(2 * PI * i / 40);
        printf("cx: %lf\n", cx);
        double rad = 20 - 10 * sx;
        printf("rad: %lf\n", rad);
        double x = 150 + 100 * cx;
        printf("x:  %lf\n", x);
        double y = 100 + 50 * sx;
        printf("y:  %lf\n", y);
    }
}