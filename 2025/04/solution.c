#include <stdbool.h>
#include <stdio.h>

// #include "sample_input.c"
#include "input.c"

int hasroll(int row, int col) {
  if (row < 0 || row > NROWS - 1 || col < 0 || col > NCOLS - 1)
    return false;
  return map[row][col] == '@';
}

int neighbours(int row, int col) {
  int count = 0;
  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      if (dr == 0 && dc == 0)
        continue;
      if (hasroll(row + dr, col + dc))
        count++;
    }
  }
  return count;
}

int part1(void) {
  int count = 0;
  for (int row = 0; row < NROWS; row++) {
    for (int col = 0; col < NCOLS; col++) {
      if (hasroll(row, col) && neighbours(row, col) < 4) {
        count++;
        putchar('x');
      } else if (hasroll(row, col)) {
        putchar('@');
      } else {
        putchar('.');
      }
    }
    printf("\n");
  }
  return count;
}

int main(void) {
  printf("part 1: %d\n", part1());
  return 0;
}
