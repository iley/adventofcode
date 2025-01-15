#include <stdio.h>
#include <stdlib.h>

#include "input.h"

#define INPUT(row, col)                                                        \
  (((row) < 0 || (row) >= rows || (col) < 0 || (col) >= cols)                  \
       ? ' '                                                                   \
       : input[(row) * cols + (col)])
#define MAP(row, col) map[(row) * cols + (col)]

int floodfill(const char *input, int *map, int rows, int cols, int row, int col,
              int color) {
  static int d_row[] = {-1, 0, 1, 0};
  static int d_col[] = {0, -1, 0, 1};

  if (MAP(row, col) != 0) {
    return 0;
  }

  MAP(row, col) = color;

  int area = 1;
  for (int i = 0; i < 4; i++) {
    int next_row = row + d_row[i];
    int next_col = col + d_col[i];

    if (INPUT(row, col) != INPUT(next_row, next_col))
      continue;

    area += floodfill(input, map, rows, cols, next_row, next_col, color);
  }

  return area;
}

int point_perimeter(const char *input, int rows, int cols, int row, int col) {
  static int d_row[] = {-1, 0, 1, 0};
  static int d_col[] = {0, -1, 0, 1};

  int perimeter = 0;
  for (int i = 0; i < 4; i++) {
    int next_row = row + d_row[i];
    int next_col = col + d_col[i];

    if (INPUT(next_row, next_col) != INPUT(row, col)) {
      perimeter++;
    }
  }
  return perimeter;
}

long long part1(const char *input, int rows, int cols) {
  int *map = (int *)malloc(sizeof(int) * rows * cols);
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      MAP(row, col) = 0;
    }
  }

  int colors = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      int area = floodfill(input, map, rows, cols, row, col, colors + 1);
      if (area > 0) {
        colors++;
      }
    }
  }

  long long total_cost = 0;

  for (int c = 1; c <= colors; c++) {
    long long area = 0;
    long long perimeter = 0;
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        if (MAP(row, col) != c)
          continue;

        area++;
        perimeter += point_perimeter(input, rows, cols, row, col);
      }
    }

    long long cost = area * perimeter;
    // printf("plot %d has area %lld, perimeter %lld, cost %lld\n", c, area,
    // perimeter, cost);
    total_cost += cost;
  }

  return total_cost;
}

#undef MAP
#undef INPUT

int main(void) {
  printf("** sample **\n");
  printf("part 1: %lld\n", part1(sample, sample_rows, sample_cols));

  printf("** solution **\n");
  printf("part 1: %lld\n", part1(input, input_rows, input_cols));

  return 0;
}
