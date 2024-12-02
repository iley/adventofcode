#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// #include "sample.h"
#include "input.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

int sign(int val) {
  if (val < 0) {
    return -1;
  } else if (val > 0) {
    return 1;
  } else {
    return 0;
  }
}

bool is_safe(int *sample) {
  int first_sign = sign(sample[1] - sample[0]);
  for (int i = 1; sample[i]; i++) {
    if (sign(sample[i] - sample[i - 1]) != first_sign) {
      return false;
    }
    int diff = abs(sample[i] - sample[i - 1]);
    if (diff < 1 || diff > 3) {
      return false;
    }
  }
  return true;
}

bool is_safe_dampened(int *sample) {
  int buffer[10];

  if (is_safe(sample)) {
    return true;
  }

  for (int i = 0; sample[i]; i++) {

    // copy the sample
    int j;
    for (j = 0; sample[j]; j++) {
      buffer[j] = sample[j];
    }
    buffer[j] = 0;

    // remove element i from the copy
    for (j = i; sample[j]; j++) {
      buffer[j] = buffer[j + 1];
    }

    if (is_safe(buffer)) {
      return true;
    }
  }

  return false;
}

int part1() {
  int total = 0;
  for (int i = 0; i < ARRAY_SIZE(input); i++) {
    if (is_safe(input[i])) {
      total++;
    }
  }
  return total;
}

int part2() {
  int total = 0;
  for (int i = 0; i < ARRAY_SIZE(input); i++) {
    if (is_safe_dampened(input[i])) {
      total++;
    }
  }
  return total;
}

int main() {
  printf("part 1 solution: %d\n", part1());
  printf("part 2 solution: %d\n", part2());
  return 0;
}
