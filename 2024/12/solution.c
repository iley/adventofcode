#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

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

  free(map);

  return total_cost;
}

int calculate_area(int *map, int rows, int cols, int color) {
  int total_area = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (MAP(row, col) == color) {
        total_area++;
      }
    }
  }
  return total_area;
}

typedef struct {
  int row;
  int col;
  int neighbour_row;
  int neighbour_col;
} border_cell_t;

bool is_adjacent(border_cell_t first, border_cell_t second) {
  int drow = first.row - second.row;
  int dcol = first.col - second.col;

  bool cells_are_adjacent = drow == 0 && (dcol == 1 || dcol == -1) || dcol == 0 && (drow == 1 || drow == -1);
  if (!cells_are_adjacent) {
    return false;
  }

  int ndrow = first.neighbour_row - second.neighbour_row;
  int ndcol = first.neighbour_col - second.neighbour_col;
  return ndrow == drow && ndcol == dcol;
}

int color_border(border_cell_t* border_cells, int* border_map, int border_cell_count, int index, int color) {
  if (border_map[index] != 0) {
    return 0;
  }

  border_map[index] = color;

  int total_length = 1;
  for (int i = 0; i < border_cell_count; i++) {
    if (i == index) continue;

    if (is_adjacent(border_cells[index], border_cells[i])) {
      int adjacent_len = color_border(border_cells, border_map, border_cell_count, i, color);
      total_length += adjacent_len;
    }
  }

  return total_length;
}

int calculate_sides(int *map, int rows, int cols, int color) {
  static int d_row[] = {-1, 0, 1, 0};
  static int d_col[] = {0, -1, 0, 1};

  border_cell_t *border_cells = NULL;
  
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (MAP(row, col) != color) continue;

      for (int i = 0; i < 4; i++) {
        int neighbour_row = row + d_row[i];
        int neighbour_col = col + d_col[i];

        if (MAP(neighbour_row, neighbour_col) != color) {
          // it's a border!
          border_cell_t cell = {
            .row = row,
            .col = col,
            .neighbour_row = neighbour_row,
            .neighbour_col = neighbour_col,
          };

          arrput(border_cells, cell);
        }
      }
    }
  }

  int border_cell_count = arrlen(border_cells);

  int* border_map = (int*)malloc(border_cell_count);
  for (int i = 0; i < border_cell_count; i++) {
    border_map[i] = 0;
  }

  int border_colors = 0;
  for (int i = 0; i < border_cell_count; i++) {
    int border_length = color_border(border_cells, border_map, border_cell_count, i, border_colors+1);
    if (border_length > 0) {
      border_colors++;
    }
  }

  free(border_map);
  return border_colors;
}

long long part2(const char *input, int rows, int cols) {
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

  for (int color = 1; color <= colors; color++) {
    long long area = calculate_area(map, rows, cols, color);
    long long sides = calculate_sides(map, rows, cols, color);

    long long cost = area * sides;
    // printf("plot %d has area %lld, sides %lld, cost %lld\n", color, area, sides, cost);
    total_cost += cost;
  }

  free(map);
  return total_cost;
}

#undef MAP
#undef INPUT

int main(void) {
  printf("** sample **\n");
  printf("part 1: %lld\n", part1(sample, sample_rows, sample_cols));
  printf("part 2: %lld\n", part2(sample, sample_rows, sample_cols));

  printf("** solution **\n");
  printf("part 1: %lld\n", part1(input, input_rows, input_cols));
  printf("part 2: %lld\n", part2(input, input_rows, input_cols));

  return 0;
}
