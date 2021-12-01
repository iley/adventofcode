#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int width = 31;
const int height = 323;

int count_trees(char *map, int dx, int dy) {
    int n_trees = 0;
    int x = 0;
    for (int y = 0; y < height; y += dy) {
        if (map[x + y*width] == '#') {
            n_trees++;
        }
        x = (x + dx) % width;
    }
    return n_trees;
}

int main(int argc, char *argv[]) {
    static char map[width*height];

    int i = 0;

    while (i < width*height) {
        int ch = fgetc(stdin);
        assert(ch != EOF);
        if (ch == '.' || ch == '#') {
            map[i] = ch;
            i++;
        }
    }

    const int n_ans = 5;
    int ans[n_ans];

    ans[0] = count_trees(map, 1, 1);
    ans[1] = count_trees(map, 3, 1);
    ans[2] = count_trees(map, 5, 1);
    ans[3] = count_trees(map, 7, 1);
    ans[4] = count_trees(map, 1, 2);

    long long int mul = 1;

    for (int i = 0; i < n_ans; i++) {
        printf("answer #%d is %d\n", i+1, ans[i]);
        mul *= ans[i];
    }

    printf("the multiple is %lld\n", mul);

    return EXIT_SUCCESS;
}
