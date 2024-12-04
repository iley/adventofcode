#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "input.h"

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

bool match(const char *buf) {
  return strcmp(buf, "XMAS") == 0 || strcmp(buf, "SAMX") == 0;
}

int part1(const char **input, int rows, int cols) {
#define GET(r, c)                                                              \
  (((r) >= 0 && (r) < rows && (c) >= 0 && (c) < cols) ? input[r][c] : ' ')

  int total = 0;
  char buf[5];
  buf[4] = 0;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {

      // Horizontal
      for (int i = 0; i < 4; i++) {
        buf[i] = GET(row, col + i);
      }
      match(buf) && total++;

      // Vertical
      for (int i = 0; i < 4; i++) {
        buf[i] = GET(row + i, col);
      }
      match(buf) && total++;

      // 1st diagonal
      for (int i = 0; i < 4; i++) {
        buf[i] = GET(row + i, col + i);
      }
      match(buf) && total++;

      // 2nd diagonal
      for (int i = 0; i < 4; i++) {
        buf[i] = GET(row + i, col - i);
      }
      match(buf) && total++;
    }
  }

  return total;

#undef GET
}

int main() {
  printf("Sample part 1 solution: %d\n",
         part1(sample, ARRSIZE(sample), strlen(sample[0])));
  printf("Part 1 solution: %d\n",
         part1(input, ARRSIZE(input), strlen(input[0])));
  return 0;
}
