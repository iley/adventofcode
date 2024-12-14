#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include "input.h"

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

typedef struct {
  char id;
  int row;
  int col;
} antenna_t;

antenna_t *parse_input(const char **input, int rows, int cols) {
  antenna_t *antennae = NULL;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (input[row][col] == '.') {
        continue;
      }

      antenna_t antenna = {.id = input[row][col], .row = row, .col = col};

      arrpush(antennae, antenna);
    }
  }

  return antennae;
}

int compare_antennae(const void *l, const void *r) {
  antenna_t *left = (antenna_t *)l;
  antenna_t *right = (antenna_t *)r;
  return left->id - right->id;
}

int part1(antenna_t *antennae, int rows, int cols) {
  int *map = (int *)malloc(sizeof(int) * rows * cols);
#define M(r, c) map[(r) * cols + (c)]

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      M(row, col) = 0;
    }
  }

  qsort(antennae, arrlen(antennae), sizeof(antenna_t), compare_antennae);

  int i = 0;
  while (i < arrlen(antennae)) {
    int c = 0;
    for (int j = i; j < arrlen(antennae) && antennae[i].id == antennae[j].id;
         j++) {
      c++;
    }

    for (int j = i; j < i + c; j++) {
      for (int k = j + 1; k < i + c; k++) {
        int anode1_row = antennae[j].row - (antennae[k].row - antennae[j].row);
        int anode1_col = antennae[j].col - (antennae[k].col - antennae[j].col);

        if (anode1_row >= 0 && anode1_row < rows && anode1_col >= 0 &&
            anode1_col < cols) {
          M(anode1_row, anode1_col)++;
        }

        int anode2_row = antennae[k].row - (antennae[j].row - antennae[k].row);
        int anode2_col = antennae[k].col - (antennae[j].col - antennae[k].col);

        if (anode2_row >= 0 && anode2_row < rows && anode2_col >= 0 &&
            anode2_col < cols) {
          M(anode2_row, anode2_col)++;
        }
      }
    }

    i += c;
  }

  int total = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (M(row, col) > 0) {
        // printf("#");
        total++;
      } else {
        // printf(".");
      }
    }
    // printf("\n");
  }

#undef M

  free(map);
  return total;
}

int part2(antenna_t *antennae, int rows, int cols) {
  int *map = (int *)malloc(sizeof(int) * rows * cols);
#define M(r, c) map[(r) * cols + (c)]

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      M(row, col) = 0;
    }
  }

  qsort(antennae, arrlen(antennae), sizeof(antenna_t), compare_antennae);

  int i = 0;
  while (i < arrlen(antennae)) {
    int c = 0;
    for (int j = i; j < arrlen(antennae) && antennae[i].id == antennae[j].id;
         j++) {
      c++;
    }

    for (int j = i; j < i + c; j++) {
      for (int k = j + 1; k < i + c; k++) {
        int a1_row = antennae[j].row;
        int a1_col = antennae[j].col;
        int a2_row = antennae[k].row;
        int a2_col = antennae[k].col;

        for (int k = 0; k < 50; k++) {
          int anode1_row = a1_row - (a2_row - a1_row) * k;
          int anode1_col = a1_col - (a2_col - a1_col) * k;

          if (anode1_row >= 0 && anode1_row < rows && anode1_col >= 0 &&
              anode1_col < cols) {
            M(anode1_row, anode1_col)++;
          }

          int anode2_row = a2_row - (a1_row - a2_row) * k;
          int anode2_col = a2_col - (a1_col - a2_col) * k;

          if (anode2_row >= 0 && anode2_row < rows && anode2_col >= 0 &&
              anode2_col < cols) {
            M(anode2_row, anode2_col)++;
          }
        }
      }
    }

    i += c;
  }

  int total = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (M(row, col) > 0) {
        // printf("#");
        total++;
      } else {
        // printf(".");
      }
    }
    // printf("\n");
  }

#undef M

  free(map);
  return total;
}

int main() {
  {
    printf(" -- sample --\n");
    int rows = ARRSIZE(sample);
    int cols = strlen(sample[0]);
    antenna_t *antennae = parse_input(sample, rows, cols);
    printf("parsed %td antennae\n", arrlen(antennae));
    printf("part 1 solution: %d\n", part1(antennae, rows, cols));
    printf("part 2 solution: %d\n", part2(antennae, rows, cols));

    arrfree(antennae);
  }

  {
    printf(" -- real input --\n");
    int rows = ARRSIZE(input);
    int cols = strlen(input[0]);
    antenna_t *antennae = parse_input(input, rows, cols);
    printf("parsed %td antennae\n", arrlen(antennae));
    printf("part 1 solution: %d\n", part1(antennae, rows, cols));
    printf("part 2 solution: %d\n", part2(antennae, rows, cols));

    arrfree(antennae);
  }

  return 0;
}
