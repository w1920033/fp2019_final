#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"

static unsigned char buf[HEIGHT][WIDTH][3];
static int filecnt = 0;
static char fname[100];

void img_clear(void)
{
    int i, j;
    for (j = 0; j < HEIGHT; ++j)
    {
        for (i = 0; i < WIDTH; ++i)
        {
            buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = 255;
        }
    }
}

void img_write(void)
{
    sprintf(fname, "img/img%04d.ppm", ++filecnt);
    FILE *f = fopen(fname, "wb");
    if (f == NULL)
    {
        fprintf(stderr, "can't open %s\n", fname);
        exit(1);
    }
    fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    fwrite(buf, sizeof(buf), 1, f);
    fclose(f);
}

void img_putpixel(struct color c, int x, int y)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    {
        return;
    }
    buf[HEIGHT - y - 1][x][0] = c.r;
    buf[HEIGHT - y - 1][x][1] = c.g;
    buf[HEIGHT - y - 1][x][2] = c.b;
}

void img_fillcircle(struct color c, double x, double y, double r)
{
    int imin = (int)(x - r - 1), imax = (int)(x + r + 1);
    int jmin = (int)(y - r - 1), jmax = (int)(y + r + 1);
    int i, j;
    for (j = jmin; j <= jmax; ++j)
    {
        for (i = imin; i <= imax; ++i)
        {
            if ((x - i) * (x - i) + (y - j) * (y - j) <= r * r)
            {
                img_putpixel(c, i, j);
            }
        }
    }
}

void img_fillrect(struct color c, double x, double y, double w, double h)
{
    int imin = (int)(x - w / 2), imax = (int)(x + w / 2);
    int jmin = (int)(y - h / 2), jmax = (int)(y + h / 2);
    int i, j;
    for (j = jmin; j <= jmax; ++j)
    {
        for (i = imin; i <= imax; ++i)
        {
            img_putpixel(c, i, j);
        }
    }
}

void img_fillellipsedonut(struct color c, double x, double y, double rx1, double ry1, double rx2, double ry2) {
  int imin = (int)(x - rx1 - 1), imax = (int)(x + rx1 + 1);
  int jmin = (int)(y - ry1 - 1), jmax = (int)(y + ry1 + 1);
  int i, j;
  for(j = jmin; j <= jmax; ++j) {
    for(i = imin; i <= imax; ++i) {
      if((x-i)*(x-i)/(rx1*rx1) + (y-j)*(y-j)/(ry1*ry1) <= 1.0 || (x-i)*(x-i)/(rx2*rx2) + (y-j)*(y-j)/(ry2*ry2) >= 1.0 ) {
        img_putpixel(c, i, j);
      }
    }
  }
}

static double oprod(double a, double b, double c, double d)
{
    return a * d - b * c;
}

static int isinside(double x, double y, int n, double ax[], double ay[])
{
    int i;
    for (i = 0; i < n; ++i)
    {
        if (oprod(ax[i + 1] - ax[i], ay[i + 1] - ay[i], x - ax[i], y - ay[i]) < 0)
        {
            return 0;
        }
    }
    return 1;
}

static double amax(int n, double a[])
{
    double m = a[0];
    int i;
    for (i = 0; i < n; ++i)
    {
        if (m < a[i])
        {
            m = a[i];
        }
    }
    return m;
}

static double amin(int n, double a[])
{
    double m = a[0];
    int i;
    for (i = 0; i < n; ++i)
    {
        if (m > a[i])
        {
            m = a[i];
        }
    }
    return m;
}

void img_fillconvex(struct color c, int n, double ax[], double ay[])
{
    int xmax = (int)(amax(n, ax) + 1);
    int xmin = (int)(amin(n, ax) - 1);
    int ymax = (int)(amax(n, ay) + 1);
    int ymin = (int)(amin(n, ay) - 1);
    int i, j;
    for (i = xmin; i <= xmax; ++i)
    {
        for (j = ymin; j <= ymax; ++j)
        {
            if (isinside(i, j, n, ax, ay))
            {
                img_putpixel(c, i, j);
            }
        }
    }
}

void img_filltriangle(struct color c, double x0, double y0, double x1, double y1, double x2, double y2)
{
    double ax1[] = {x0, x1, x2, x0};
    double ax2[] = {x0, x2, x1, x0};
    double ay1[] = {y0, y1, y2, y0};
    double ay2[] = {y0, y2, y1, y0};
    img_fillconvex(c, 3, ax1, ay1);
    img_fillconvex(c, 3, ax2, ay2);
}
