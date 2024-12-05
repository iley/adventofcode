#include <stdbool.h>
#include <stdio.h>

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

// #include "sample.h"
#include "input.h"

void print_update(int *update) {
  for (int i = 0; update[i]; i++) {
    printf("%d, ", update[i]);
  }
  printf("\n");
}

bool is_valid(int *update) {
  for (int i = 0; i < ARRSIZE(rules); i++) {
    int left = rules[i].left;
    int right = rules[i].right;

    int lpos = -1;
    int rpos = -1;
    for (int j = 0; update[j]; j++) {
      if (update[j] == left) {
        lpos = j;
      } else if (update[j] == right) {
        rpos = j;
      }
    }

    if (lpos != -1 && rpos != -1 && lpos > rpos) {
      // printf("Rule broken! %d > %d\n", lpos, rpos);
      return false;
    }
  }

  return true;
}

int update_len(int *update) {
  int len = 0;
  for (int i = 0; update[i]; i++) {
    len++;
  }
  return len;
}

int midpoint(int *update) { return update[update_len(update) / 2]; }

int part1() {
  int sum = 0;
  for (int i = 0; i < ARRSIZE(updates); i++) {
    // print_update(updates[i]);
    if (is_valid(updates[i])) {
      int mid = midpoint(updates[i]);
      // printf("valid! midpoint = %d\n", mid);
      sum += midpoint(updates[i]);
    }
  }
  return sum;
}

int main(int argc, char **argv) {
  printf("Part 1 solution: %d\n", part1());

  return 0;
}
