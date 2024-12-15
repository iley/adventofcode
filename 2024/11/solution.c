#include <stdio.h>
#include <stdlib.h>

#include "input.h"

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

typedef struct pebble_t {
  long long value;
  struct pebble_t *next;
} pebble_t;

pebble_t *pebbles_new(int *input, int input_size) {
  pebble_t *head = NULL;
  pebble_t *tail = NULL;

  for (int i = 0; i < input_size; i++) {
    pebble_t *new_pebble = (pebble_t *)malloc(sizeof(pebble_t));

    new_pebble->value = input[i];
    new_pebble->next = NULL;

    if (head == NULL) {
      head = new_pebble;
    } else {
      tail->next = new_pebble;
    }

    tail = new_pebble;
  }

  return head;
}

void pebbles_free(pebble_t *head) {
  if (head == NULL) {
    return;
  }

  while (head) {
    pebble_t *new_head = head->next;
    free(head);
    head = new_head;
  }
}

long long pebbles_len(pebble_t *head) {
  long long len = 0;
  for (pebble_t *p = head; p; p = p->next) {
    len++;
  }
  return len;
}

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

pebble_t *step(pebble_t *head) {
  for (pebble_t *p = head; p; p = p->next) {
    if (p->value == 0) {
      // printf("0 -> 1\n");
      p->value = 1;
      continue;
    }

    int dlen = digits_len(p->value);
    if (dlen % 2 == 0) {
      long long factor = pow10(dlen / 2);
      long long left_value = p->value / factor;
      long long right_value = p->value % factor;

      /*
      printf("split %lld to %lld and %lld (factor = %lld\n", p->value,
             left_value, right_value, factor);
             */

      p->value = left_value;
      pebble_t *new_pebble = (pebble_t *)malloc(sizeof(pebble_t));
      new_pebble->value = right_value;
      new_pebble->next = p->next;
      p->next = new_pebble;

      // skip the new pebble
      p = p->next;
      continue;
    }

    // printf("%lld * 2024 = %lld\n", p->value, p->value * 2024);
    p->value *= 2024;
  }

  return head;
}

long long part1(int *input, int input_size) {
  pebble_t *head = pebbles_new(input, input_size);

  for (int i = 0; i < 25; i++) {
    head = step(head);
  }

  return pebbles_len(head);
}

int main() {
  printf("-- sample --\n");
  printf("part 1: %lld\n", part1(sample, ARRSIZE(sample)));

  printf("-- answer --\n");
  printf("part 1: %lld\n", part1(input, ARRSIZE(input)));
  return 0;
}
