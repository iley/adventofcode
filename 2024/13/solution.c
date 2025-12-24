#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "input.h"

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

int solve_machine(machine_t machine) {
  int min_cost = INT_MAX;

  for (int a_guess = 0; a_guess <= 100; a_guess++) {
    for (int b_guess = 0; b_guess <= 100; b_guess++) {
      if (a_guess * machine.a_x + b_guess * machine.b_x == machine.prize_x
          && a_guess * machine.a_y + b_guess * machine.b_y == machine.prize_y) {
        int cost = a_guess * 3 + b_guess;
        if (cost < min_cost) {
          min_cost = cost;
        }
      }
    }
  }

  return min_cost;
}

int part1(int machines_count, machine_t *machines) {
  int total = 0;
  for (int i = 0; i < machines_count; i++) {
    int cost = solve_machine(machines[i]);
    if (cost == INT_MAX) {
      printf("Machine #%d: no solution\n", i+1);
    } else {
      printf("Machine #%d: %d\n", i+1, cost);
      total += cost;
    }
  }

  return total;
}

int main(void) {
  printf("part 1: %d\n", part1(ARRSIZE(machines), machines));
  return 0;
}
