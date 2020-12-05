#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const int max_strlen = 100;

int main() {
    int min, max;
    char ch;
    static char pass[max_strlen];

    int n_valid = 0;

    while (true) {
        if (scanf("%d-%d %c: %s", &min, &max, &ch, pass) <= 0) {
            break;
        }

        size_t len = strlen(pass);
        int count = 0;
        for (size_t i = 0; i < len; i++) {
            if (pass[i] == ch) {
                count++;
            }
        }

        if (min <= count && count <= max) {
            n_valid++;
        }
    }

    printf("number of valid passwords: %d\n", n_valid);

    return EXIT_SUCCESS;
}
