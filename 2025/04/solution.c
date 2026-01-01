#include <stdbool.h>
#include <stdio.h>

// #include "sample_input.c"
#include "input.c"

char map[NROWS][NCOLS];

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
      if (hasroll(row, col) && neighbours(row, col) < 4)
        count++;
    }
  }
  return count;
}

int remove_accessible_rolls(void) {
  static char newmap[NROWS][NCOLS];

  int count = 0;
  for (int row = 0; row < NROWS; row++) {
    for (int col = 0; col < NCOLS; col++) {
      if (hasroll(row, col) && neighbours(row, col) < 4) {
        newmap[row][col] = '.';
        count++;
      } else {
        newmap[row][col] = map[row][col];
      }
    }
  }

  for (int row = 0; row < NROWS; row++)
    for (int col = 0; col < NCOLS; col++)
      map[row][col] = newmap[row][col];

  return count;
}

int part2(void) {
  int total = 0;

  while (true) {
    int removed = remove_accessible_rolls();
    if (removed == 0)
      break;

    total += removed;
  }

  return total;
}

int main(void) {
  for (int row = 0; row < NROWS; row++)
    for (int col = 0; col < NCOLS; col++)
      map[row][col] = input_map[row][col];
  // printf("part 1: %d\n", part1());
  printf("part 2: %d\n", part2());
  return 0;
}
