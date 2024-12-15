#include <stdio.h>
#include <stdlib.h>

#include "input.h"

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

typedef struct {
  int *data;
  int rows;
  int cols;
} map_t;

map_t map_alloc(int rows, int cols) {
  map_t map = {
      .data = (int *)malloc(sizeof(int) * rows * cols),
      .rows = rows,
      .cols = cols,
  };
  for (int i = 0; i < rows * cols; i++) {
    map.data[i] = 0;
  }
  return map;
};

void map_free(map_t map) { free(map.data); }

int map_get(map_t map, int row, int col) {
  return map.data[row * map.cols + col];
}

void map_set(map_t map, int row, int col, int value) {
  map.data[row * map.cols + col] = value;
}

int dfs(map_t map, map_t visited, int row, int col) {
  if (map_get(map, row, col) == 9) {
    map_set(visited, row, col, 1);
    return 1;
  }

  int row_offsets[] = {-1, 0, 1, 0};
  int col_offsets[] = {0, -1, 0, 1};

  int sum = 0;
  for (int i = 0; i < ARRSIZE(row_offsets); i++) {
    int next_row = row + row_offsets[i];
    int next_col = col + col_offsets[i];

    if (next_row < 0 || next_row >= map.rows || next_col < 0 ||
        next_col >= map.cols) {
      continue;
    }

    if (map_get(visited, next_row, next_col)) {
      continue;
    }

    if (map_get(map, next_row, next_col) != map_get(map, row, col) + 1) {
      continue;
    }

    sum += dfs(map, visited, next_row, next_col);
  }

  return sum;
}

int trailhead_score(map_t map, int row, int col) {
  map_t visited = map_alloc(map.rows, map.cols);
  int result = dfs(map, visited, row, col);
  map_free(visited);
  return result;
}

int part1(map_t map) {
  int score_sum = 0;
  for (int row = 0; row < map.rows; row++) {
    for (int col = 0; col < map.cols; col++) {
      if (map_get(map, row, col) == 0) {
        int score = trailhead_score(map, row, col);
        // printf("trailhead score for (%d, %d) is %d\n", row, col, score);
        score_sum += score;
      }
    }
  }
  return score_sum;
}

int main() {
  printf("-- sample --\n");
  map_t sample_map = {
      .data = sample,
      .rows = sample_rows,
      .cols = sample_cols,
  };
  printf("part 1: %d\n", part1(sample_map));

  printf("-- solution --\n");
  map_t map = {
      .data = input,
      .rows = input_rows,
      .cols = input_cols,
  };
  printf("part 1: %d\n", part1(map));
  return 0;
}
