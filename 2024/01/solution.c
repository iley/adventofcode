#include <stdio.h>
#include <stdlib.h>

#include "input.h"

#define ARR_SIZE(x) (sizeof(x) / sizeof(x[0]))

int compare_int(const void *a, const void *b) {
  return *((int *)a) - *((int *)b);
}

int part1() {
  qsort(input_left, ARR_SIZE(input_left), sizeof(input_left[0]), compare_int);
  qsort(input_right, ARR_SIZE(input_right), sizeof(input_right[0]),
        compare_int);

  int result = 0;
  for (int i = 0; i < ARR_SIZE(input_left); i++) {
    result += abs(input_left[i] - input_right[i]);
  }

  return result;
}

int part2() {
  int result = 0;

  for (int i = 0; i < ARR_SIZE(input_left); i++) {
    int count = 0;
    for (int j = 0; j < ARR_SIZE(input_right); j++) {
      if (input_right[j] == input_left[i]) {
        count++;
      }
    }
    result += input_left[i] * count;
  }

  return result;
}

int main() {
  int part1_result = part1();
  printf("Part 1 answer: %d\n", part1_result);

  int part2_result = part2();
  printf("Part 2 answer: %d\n", part2_result);

  return 0;
}
