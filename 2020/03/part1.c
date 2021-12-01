#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int width = 31;
const int height = 323;

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

    int n_trees = 0;
    int dx = 3;
    for (int y = 0; y < height; y++) {
        int x = (y * dx) % width;
        if (map[x + y*width] == '#') {
            n_trees++;
        }
    }

    printf("the answer is %d", n_trees);

    return EXIT_SUCCESS;
}
