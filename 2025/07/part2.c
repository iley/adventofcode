#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

// #include "sample_input.c"
#include "input.c"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct key_t {
  int row;
  int col;
} key_t;

typedef struct table_t {
  key_t key;
  int value;
} table_t;

table_t *table;

char map[ROWS][COLS] = {0};

int find_start_col(void) {
  for (int col = 0; col < COLS; col++)
    if (map[0][col] == 'S')
      return col;

  return -1;
}

int traverse(int row, int col) {
  // printf("traverse(%d, %d)\n", row, col);

  if (row >= ROWS - 1)
    return 1;

  if (map[row][col] == '.' || map[row][col] == 'S')
    return traverse(row + 1, col);

  if (map[row][col] == '^') {
    int left = 0;
    if (col > 0)
      left = traverse(row + 1, col - 1);

    int right = 0;
    if (col < COLS - 1)
      right = traverse(row + 1, col + 1);

    return left + right;
  }

  assert(false);
  return -1;
}

int traverse_mem(int row, int col) {
  key_t key = {.row = row, .col = col};
  int idx = hmgeti(table, key);
  if (idx != -1) {
    return table[idx].value;
  }

  int result = traverse(row, col);
  hmput(table, key, result);
  return result;
}

int main(void) {
  for (int row = 0; row < ROWS; row++)
    for (int col = 0; col < COLS; col++)
      map[row][col] = input_strings[row][col];

  int start_col = find_start_col();
  assert(start_col != -1);
  int answer = traverse_mem(0, start_col);
  printf("%d\n", answer);

  return 0;
}
