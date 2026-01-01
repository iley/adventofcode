#include <stdbool.h>
#include <stdio.h>

#include "input.h"

#define ARRLEN(a) (sizeof(a) / sizeof(a[0]))

int count_digits(long n) {
  int digits = 0;
  while (n > 0) {
    digits++;
    n /= 10;
  }
  return digits;
}

bool is_invalid(long id) {
  int ndigits = count_digits(id);
  int w = ndigits / 2;

  int divider = 1;
  for (int i = 0; i < w; i++) {
    divider *= 10;
  }

  return (id / divider) == (id % divider);
}

long part1(range_t input[], int n) {
  long sum = 0;
  for (int i = 0; i < n; i++) {
    long start = input[i].start;
    long end = input[i].end;
    // printf("range %ld..%ld\n", start, end);
    for (long id = start; id <= end; id++) {
      if (is_invalid(id)) {
        sum += id;
        // printf("invalid id %ld\n", id);
      }
    }
  }
  return sum;
}

bool is_repeated(long n, long div) {
  long segment = n % div;
  if (segment < div / 10) {
    return false; // there are leading zeros, bail out
  }
  long rest = n / div;
  while (rest > 0) {
    long next_segment = rest % div;
    rest = rest / div;
    if (next_segment != segment) {
      return false;
    }
  }
  return true;
}

bool is_invalid_v2(long id) {
  for (long div = 10; id / div != 0; div *= 10) {
    if (is_repeated(id, div)) {
      return true;
    }
  }
  return false;
}

long part2(range_t input[], int n) {
  long sum = 0;
  for (int i = 0; i < n; i++) {
    long start = input[i].start;
    long end = input[i].end;
    // printf("range %ld..%ld\n", start, end);
    for (long id = start; id <= end; id++) {
      if (is_invalid_v2(id)) {
        sum += id;
        // printf("invalid id %ld\n", id);
      }
    }
  }
  return sum;
}

int main() {
  printf("part 1: %ld\n", part1(input, ARRLEN(input)));
  printf("part 2: %ld\n", part2(input, ARRLEN(input)));
  return 0;
}
