#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *slurp(const char *filepath) {
  FILE *file = fopen(filepath, "r");
  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = malloc(size + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, size, file);
  buffer[size] = '\0';

  fclose(file);
  return buffer;
}

int count_digits(const char *str) {
  int digits = 0;
  while (isdigit(str[digits])) {
    digits++;
  }
  return digits;
}

// Returns the length of the matched string.
int match(const char *input, int *outa, int *outb) {
  const char *str = input;
  if (strncmp(str, "mul(", strlen("mul(")) != 0) {
    return 0;
  }

  // First argument.
  str += strlen("mul(");

  int first_arg_len = count_digits(str);
  if (first_arg_len < 1 || first_arg_len > 3) {
    return 0;
  }

  *outa = atoi(str);
  str += first_arg_len;

  // Comma.
  if (*str != ',') {
    return 0;
  }
  str++;

  // Second argument.
  int second_arg_len = count_digits(str);
  if (second_arg_len < 1 || second_arg_len > 3) {
    return 0;
  }

  *outb = atoi(str);

  str += second_arg_len;
  if (*str != ')') {
    return 0;
  }

  return str - input;
}

int part1(const char *input) {
  int sum = 0;
  for (const char *str = input; *str; str++) {
    int a, b;
    if (match(str, &a, &b)) {
      sum += a * b;
    }
  }
  return sum;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILE\n", argv[0]);
    return 1;
  }

  char *input = slurp(argv[1]);
  assert(input);

  printf("Part 1 solution: %d\n", part1(input));
}
