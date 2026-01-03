#include "input.c"

#include <stdbool.h>
#include <stdio.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

long largest_area(void) {
  long max_area = -1;
  for (int i = 0; i < NPOINTS; i++) {
    for (int j = i + 1; j < NPOINTS; j++) {
      point_t p1 = points[i];
      point_t p2 = points[j];

      long x1 = MIN(p1.x, p2.x);
      long x2 = MAX(p1.x, p2.x);
      long y1 = MIN(p1.y, p2.y);
      long y2 = MAX(p1.y, p2.y);

      long area = (x2 - x1 + 1) * (y2 - y1 + 1);
      if (area > max_area)
        max_area = area;
    }
  }
  return max_area;
}

int main(void) {
  printf("%ld\n", largest_area());
  return 0;
}
