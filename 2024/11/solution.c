#include <stdio.h>
#include <stdlib.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include "input.h"

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

typedef struct {
  long long key;
  long long value;
} entry_t;

entry_t *cache;

int digits_len(long long value) {
  int len = 0;
  while (value > 0) {
    value /= 10;
    len++;
  }
  return len;
}

long long pow10(int pow) {
  long long result = 1;
  for (int i = 0; i < pow; i++) {
    result *= 10;
  }
  return result;
}

long long blink(long long value, int steps);

long long blink_cached(long long value, int steps) {
  int cache_key = value * 100 + steps;

  entry_t *cache_entry = hmgetp_null(cache, cache_key);
  if (cache_entry) {
    return cache_entry->value;
  }

  long long result = blink(value, steps);
  hmput(cache, cache_key, result);
  return result;
}

long long blink(long long value, int steps) {
  if (steps == 0) {
    return 1;
  }

  if (value == 0) {
    return blink_cached(1, steps - 1);
  }

  int dlen = digits_len(value);
  if (dlen % 2 == 0) {
    int factor = pow10(dlen / 2);
    long long left_value = value / factor;
    long long right_value = value % factor;

    return blink_cached(left_value, steps - 1) + blink(right_value, steps - 1);
  }

  return blink_cached(value * 2024, steps - 1);
}

long long solution(int *input, int input_size, int steps) {
  cache = NULL;

  long long sum = 0;
  for (int i = 0; i < input_size; i++) {
    sum += blink(input[i], steps);
  }

  hmfree(cache);
  return sum;
}

int main() {
  printf("-- sample --\n");
  printf("part 1: %lld\n", solution(sample, ARRSIZE(sample), 25));

  printf("-- answer --\n");
  printf("part 1: %lld\n", solution(input, ARRSIZE(input), 25));
  printf("part 2: %lld\n", solution(input, ARRSIZE(input), 75));

  return 0;
}
