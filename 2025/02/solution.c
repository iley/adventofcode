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
    printf("range %ld..%ld\n", start, end);
    for (long id = start; id <= end; id++) {
      if (is_invalid(id)) {
        sum += id;
        printf("invalid id %ld, sum = %ld\n", id, sum);
      }
    }
  }
  return sum;
}

int main() {
  printf("part 1: %ld\n", part1(input, ARRLEN(input)));
  return 0;
}
