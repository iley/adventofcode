#include <stdbool.h>
#include <stdio.h>

// #include "sample.h"
#include "input.h"

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

int operlen(long long *operands) {
  int count = 0;
  for (int i = 0; operands[i]; i++) {
    count++;
  }
  return count;
}

bool can_be_true(long long value, long long *operands, int noperands) {
  if (noperands == 1) {
    return value == operands[0];
  }

  long long last_operand = operands[noperands - 1];

  return can_be_true(value - last_operand, operands, noperands - 1) ||
         (value % last_operand == 0 &&
          can_be_true(value / last_operand, operands, noperands - 1));
}

long part1() {
  long long sum = 0;

  for (int i = 0; i < ARRSIZE(values); i++) {
    long long val = values[i];
    long long *oper = operands[i];

    if (can_be_true(val, oper, operlen(oper))) {
      printf("YES %lld\n", val);
      sum += val;
    } else {
      printf("NO  %lld\n", val);
    }
  }

  return sum;
}

int main() {
  printf("Part 1 solution: %ld\n", part1());
  return 0;
}
