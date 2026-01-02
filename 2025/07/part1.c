#include <stdio.h>

// #include "sample_input.c"
#include "input.c"

char map[ROWS][COLS] = {0};

int step(int row) {
  int split_count = 0;
  for (int col = 0; col < COLS; col++) {
    if (map[row][col] == 'S') {
      map[row][col] = '|';
      continue;
    }

    if (map[row - 1][col] == '|') {
      if (map[row][col] == '.') {
        map[row][col] = '|';
      } else if (map[row][col] == '^') {
        split_count++;
        if (col > 0)
          map[row][col - 1] = '|';
        if (col < COLS - 1)
          map[row][col + 1] = '|';
      }
    }
  }
  return split_count;
}

int main(void) {
  for (int row = 0; row < ROWS; row++)
    for (int col = 0; col < COLS; col++)
      map[row][col] = input_strings[row][col];

  int total = 0;
  for (int row = 0; row < ROWS; row++) {
    total += step(row);
  }
  printf("%d\n", total);

  return 0;
}
