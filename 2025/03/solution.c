// #include "sample_input.c"
#include "input.c"
#include <stdbool.h>
#include <stdio.h>

#define MAXBAT 12
#define ARRLEN(a) ((sizeof(a) / sizeof(a[0])))

int max_joltage(int *bank) {
  int potentials[NBAT] = {0};
  int max_digit = 0;
  int maxj = 0;
  for (int i = NBAT - 1; i >= 0; i--) {
    potentials[i] = bank[i] * 10 + max_digit;
    if (i < NBAT - 1 && potentials[i] > maxj)
      maxj = potentials[i];
    if (bank[i] > max_digit)
      max_digit = bank[i];
  }
  return maxj;
}

long part1(void) {
  int sum = 0;
  for (int i = 0; i < NBANKS; i++) {
    int maxj = max_joltage(input[i]);
    sum += maxj;
  }
  return sum;
}

long pow10(int n) {
  static long table[] = {
      1,           10,           100,           1000,      10000,
      100000,      1000000,      10000000,      100000000, 1000000000,
      10000000000, 100000000000, 1000000000000,
  };
  return table[n];
}

long max_joltage_v2(int *bank) {
  long t[MAXBAT + 1][NBAT] = {0};

  int max_digit = 0;
  for (int i = NBAT - 1; i >= 0; i--) {
    if (bank[i] > max_digit)
      max_digit = bank[i];
    t[1][i] = max_digit;
  }

  for (int nbat = 2; nbat <= MAXBAT; nbat++) {
    for (int i = NBAT - nbat; i >= 0; i--) {
      long j1 = pow10(nbat - 1) * bank[i] +
                t[nbat - 1][i + 1]; // joltage if we use this battery
      long j2 = t[nbat][i + 1];     // joltage if we don't
      if (j1 > j2)
        t[nbat][i] = j1;
      else
        t[nbat][i] = j2;
    }
  }
  return t[MAXBAT][0];
}

long part2(void) {
  long sum = 0;
  for (int i = 0; i < NBANKS; i++) {
    long maxj = max_joltage_v2(input[i]);
    sum += maxj;
  }
  return sum;
}

int main(void) {
  printf("part 1: %ld\n", part1());
  printf("part 2: %ld\n", part2());
  return 0;
}
