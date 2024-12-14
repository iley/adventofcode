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

int *make_map(const char *input) {
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

inode_t *make_inodes(const char *input) {
  inode_t *inodes = NULL;

  int len = strlen(input);
  int id = 0;
  bool isfile = true;
  int pos = 0;

  for (int i = 0; i < len; i++) {
    int len = input[i] - '0';
    inode_t inode = {
        .pos = pos,
        .len = len,
    };
    pos += len;
    if (isfile) {
      inode.id = id;
      id++;
    } else {
      inode.id = -1;
    }
    arrpush(inodes, inode);

    isfile = !isfile;
  }

  return inodes;
}

void print_map(int *map) {
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
  // print_map(map);

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
    // print_map(map);
  }

  return map;
}

int *inodes_to_map(inode_t *inodes) {
  int len_sum = 0;
  for (int i = 0; i < arrlen(inodes); i++) {
    len_sum += inodes[i].len;
  }

  int *map = NULL;
  arrsetlen(map, len_sum);
  for (int i = 0; i < arrlen(map); i++) {
    map[i] = -1;
  }

  for (int i = 0; i < arrlen(inodes); i++) {
    for (int pos = inodes[i].pos; pos < inodes[i].pos + inodes[i].len; pos++) {
      map[pos] = inodes[i].id;
    }
  }

  return map;
}

int *defrag2(inode_t *inodes) {
  for (int i = arrlen(inodes); i >= 0; i--) {
    if (inodes[i].id == -1) {
      continue;
    }

    // try finding an empty slot for this file.
    for (int j = 0; j < arrlen(inodes); j++) {
      if (inodes[j].id != -1 || inodes[j].pos >= inodes[i].pos ||
          inodes[j].len < inodes[i].len) {
        continue;
      }

      // found one
      inodes[i].pos = inodes[j].pos;
      inodes[j].pos += inodes[i].len;
      inodes[j].len -= inodes[i].len;

      if (i > 0) {
        // update the space before the file
        inodes[i - 1].len += inodes[i].len;
      }
    }
  }

  int *map = inodes_to_map(inodes);

  return map;
}

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
  int *map = make_map(input);

  map = defrag(map);

  long long answer = checksum(map);
  arrfree(map);
  return answer;
}

long long part2(const char *input) {
  inode_t *inodes = make_inodes(input);

  int *map = defrag2(inodes);

  long long answer = checksum(map);

  arrfree(inodes);
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
