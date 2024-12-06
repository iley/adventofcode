#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

enum {
  CELL_EMPTY = 0,
  CELL_OCCUPIED = 1,
  CELL_VISITED = 2,
};

enum {
  DIR_UP = 0,
  DIR_RIGHT = 1,
  DIR_DOWN = 2,
  DIR_LEFT = 3,
};

typedef struct {
  int *data;
  int cols;
  int rows;
} field_t;

field_t field_new(int rows, int cols) {
  field_t field;
  field.data = malloc(sizeof(int) * rows * cols);
  field.rows = rows;
  field.cols = cols;
  return field;
}

void field_set(field_t field, int row, int col, int value) {
  field.data[row * field.cols + col] = value;
}

int field_get(field_t field, int row, int col) {
  return field.data[row * field.cols + col];
}

int dir_turn(int dir) { return (dir + 1) % 4; }

field_t make_field(const char *input[], int rows, int cols) {
  field_t field = field_new(rows, cols);
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      char ch = input[row][col];
      int value = (ch == '#') ? CELL_OCCUPIED : CELL_EMPTY;
      field_set(field, row, col, value);
    }
  }
  return field;
}

void find_guard(const char *input[], int rows, int cols, int *out_row,
                int *out_col) {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (input[row][col] == '^') {
        *out_row = row;
        *out_col = col;
        return;
      }
    }
  }
  fprintf(stderr, "initial guard position not found\n");
  exit(1);
}

void move_guard(int row, int col, int dir, int *out_row, int *out_col) {
  switch (dir) {
  case DIR_UP:
    *out_row = row - 1;
    *out_col = col;
    break;
  case DIR_RIGHT:
    *out_row = row;
    *out_col = col + 1;
    break;
  case DIR_DOWN:
    *out_row = row + 1;
    *out_col = col;
    break;
  case DIR_LEFT:
    *out_row = row;
    *out_col = col - 1;
    break;
  }
}

void print_field(int *field, int rows, int cols, int guard_row, int guard_col,
                 int guard_dir) {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      char ch = '.';
      if (row == guard_row && col == guard_col) {
        switch (guard_dir) {
        case DIR_UP:
          ch = '^';
          break;
        case DIR_RIGHT:
          ch = '>';
          break;
        case DIR_DOWN:
          ch = 'v';
          break;
        case DIR_LEFT:
          ch = '<';
          break;
        }
      } else {
        switch (field[row * cols + col]) {
        case CELL_EMPTY:
          ch = '.';
          break;
        case CELL_OCCUPIED:
          ch = '#';
          break;
        case CELL_VISITED:
          ch = 'X';
          break;
        }
      }

      fputc(ch, stdout);
    }
    printf("\n");
  }
  printf("\n");
}

void simulate_guard(field_t field, int guard_row, int guard_col) {
  int guard_dir = DIR_UP;

  while (1) {
    // print_field(field, rows, cols, guard_row, guard_col, guard_dir);

    int new_guard_row;
    int new_guard_col;
    move_guard(guard_row, guard_col, guard_dir, &new_guard_row, &new_guard_col);

    if (new_guard_row < 0 || new_guard_row >= field.rows || new_guard_col < 0 ||
        new_guard_col >= field.cols) {
      field_set(field, guard_row, guard_col, CELL_VISITED);
      break;
    }

    if (field_get(field, new_guard_row, new_guard_col) == CELL_OCCUPIED) {
      guard_dir = dir_turn(guard_dir);
      // do not update position
    } else {
      field_set(field, guard_row, guard_col, CELL_VISITED);
      guard_row = new_guard_row;
      guard_col = new_guard_col;
    }
  }
}

int part1(const char *input[], int rows, int cols) {
  int guard_row;
  int guard_col;
  find_guard(input, rows, cols, &guard_row, &guard_col);

  field_t field = make_field(input, rows, cols);
  simulate_guard(field, guard_row, guard_col);

  int count = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (field_get(field, row, col) == CELL_VISITED) {
        count++;
      }
    }
  }

  return count;

  return 0;
}

int main() {
  int sample_rows = ARRSIZE(sample);
  int sample_cols = strlen(sample[0]);

  printf("Part 1 sample solution: %d\n",
         part1(sample, sample_rows, sample_cols));

  int rows = ARRSIZE(input);
  int cols = strlen(input[0]);

  printf("Part 1 solution: %d\n", part1(input, rows, cols));

  return 0;
}