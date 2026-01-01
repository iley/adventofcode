#include <stdbool.h>
#include <stdio.h>

// #include "sample_input.c"
#include "input.c"

bool is_fresh(long id) {
  for (int i = 0; i < NRANGES; i++) {
    if (ranges[i].start <= id && id <= ranges[i].end)
      return true;
  }
  return false;
}

long part1(void) {
  long total = 0;
  for (int i = 0; i < NINGRIDIENTS; i++)
    if (is_fresh(ingridients[i]))
      total++;

  return total;
}

int main(void) {
  printf("part 1: %ld\n", part1());
  return 0;
}
