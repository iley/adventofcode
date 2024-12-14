#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include "input.h"

#define ARRSIZE(x) (sizeof(x) / sizeof(x[0]))

typedef struct {
  int id;
  int pos;
  int len;
} inode_t;

int *makemap(const char *input) {
  int *map = NULL;

  int len = strlen(input);
  int id = 0;

  bool isfile = true;
  for (int i = 0; i < len; i++) {
    int blocks = input[i] - '0';

    if (isfile) {
      for (int j = 0; j < blocks; j++) {
        arrpush(map, id);
      }
      id++;
    } else {
      for (int j = 0; j < blocks; j++) {
        arrpush(map, -1);
      }
    }

    isfile = !isfile;
  }

  return map;
}

void printmap(int *map) {
  for (int i = 0; i < arrlen(map); i++) {
    if (map[i] == -1) {
      printf(".");
    } else if (map[i] < 10) {
      printf("%d", map[i]);
    } else {
      printf("[%d]", map[i]);
    }
  }
  printf("\n");
}

bool is_defrag_done(int *map) {
  for (int i = 1; i < arrlen(map); i++) {
    if (map[i - 1] == -1 && map[i] != -1) {
      return false;
    }
  }
  return true;
}

int *defrag(int *map) {
  // printmap(map);

  while (!is_defrag_done(map)) {
    int rightmost_block = 0;
    for (int i = arrlen(map) - 1; i >= 0; i--) {
      if (map[i] != -1) {
        rightmost_block = i;
        break;
      }
    }

    int leftmost_space = 0;
    for (int i = 0; i < arrlen(map); i++) {
      if (map[i] == -1) {
        leftmost_space = i;
        break;
      }
    }

    int t = map[rightmost_block];
    map[rightmost_block] = map[leftmost_space];
    map[leftmost_space] = t;
    // printmap(map);
  }

  return map;
}

int *defrag2(int *map) { return map; }

long long checksum(int *map) {
  long long sum = 0;
  int len = arrlen(map);

  for (int i = 0; i < len; i++) {
    if (map[i] != -1) {
      sum += map[i] * i;
    }
  }

  return sum;
}

long long part1(const char *input) {
  int *map = makemap(input);

  map = defrag(map);

  long long answer = checksum(map);
  arrfree(map);
  return answer;
}

long long part2(const char *input) {
  int *map = makemap(input);

  map = defrag2(map);

  long long answer = checksum(map);
  arrfree(map);
  return answer;
}

int main() {
  printf("-- sample --\n");
  printf("part 1: %lld\n", part1(sample));
  printf("part 2: %lld\n", part2(sample));

  printf("-- solution --\n");
  printf("part 1: %lld\n", part1(input));
  printf("part 2: %lld\n", part2(input));
  return 0;
}
