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

long long concat_sub(long long left, long long right) {
  while (right > 0) {
    long long left_digit = left % 10;
    long long right_digit = right % 10;

    if (left_digit != right_digit) {
      return -1;
    }

    left = left / 10;
    right = right / 10;
  }

  return left;
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

bool can_be_true_extended(long long value, long long *operands, int noperands) {
  if (noperands == 1) {
    return value == operands[0];
  }

  long long last_operand = operands[noperands - 1];

  return can_be_true_extended(value - last_operand, operands, noperands - 1) ||
         (value % last_operand == 0 &&
          can_be_true_extended(value / last_operand, operands,
                               noperands - 1)) ||
         (concat_sub(value, last_operand) != -1 &&
          can_be_true_extended(concat_sub(value, last_operand), operands,
                               noperands - 1));
}

long part1() {
  long long sum = 0;

  for (int i = 0; i < ARRSIZE(values); i++) {
    long long val = values[i];
    long long *oper = operands[i];

    if (can_be_true(val, oper, operlen(oper))) {
      sum += val;
    }
  }

  return sum;
}

long part2() {
  long long sum = 0;

  for (int i = 0; i < ARRSIZE(values); i++) {
    long long val = values[i];
    long long *oper = operands[i];

    if (can_be_true_extended(val, oper, operlen(oper))) {
      sum += val;
    }
  }

  return sum;
}

int main() {
  printf("Part 1 solution: %ld\n", part1());
  printf("Part 2 solution: %ld\n", part2());
  return 0;
}
