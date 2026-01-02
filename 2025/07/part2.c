#include <stdio.h>

// #include "sample_input.c"
#include "input.c"

char map[ROWS][COLS] = {0};
long paths[ROWS][COLS] = {0};

void step(int row) {
  for (int col = 0; col < COLS; col++) {
    if (map[row][col] == 'S') {
      map[row][col] = '|';
      continue;
    }

    if (map[row - 1][col] == '|') {
      if (map[row][col] == '.') {
        map[row][col] = '|';
      } else if (map[row][col] == '^') {
        if (col > 0)
          map[row][col - 1] = '|';
        if (col < COLS - 1)
          map[row][col + 1] = '|';
      }
    }
  }
}

void mark_map(void) {
  for (int row = 0; row < ROWS; row++) {
    step(row);
  }
}

long count_paths(void) {
  for (int col = 0; col < COLS; col++)
    if (map[ROWS - 1][col] == '|')
      paths[ROWS - 1][col] = 1;

  for (int row = ROWS - 2; row >= 0; row--) {
    for (int col = 0; col < COLS; col++) {
      if (map[row][col] != '|')
        continue;

      if (map[row + 1][col] == '^') {
        paths[row][col] = paths[row + 1][col - 1] + paths[row + 1][col + 1];
      } else {
        paths[row][col] = paths[row + 1][col];
      }
    }
  }

  long total = 0;
  for (int col = 0; col < COLS; col++)
    total += paths[0][col];

  return total;
}

int main(void) {
  for (int row = 0; row < ROWS; row++)
    for (int col = 0; col < COLS; col++)
      map[row][col] = input_strings[row][col];

  mark_map();
  long answer = count_paths();

  printf("%ld\n", answer);

  return 0;
}
