#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const int max_strlen = 100;

int main() {
    int first, second;
    char ch;
    static char pass[max_strlen];

    int n_valid = 0;

    while (true) {
        if (scanf("%d-%d %c: %s", &first, &second, &ch, pass) <= 0) {
            break;
        }

        size_t len = strlen(pass);

        if (first > len || second > len) {
            continue;
        }

        if ((pass[first-1] == ch && pass[second-1] != ch) ||
            (pass[first-1] != ch && pass[second-1] == ch)) {
            n_valid++;
        }
    }

    printf("number of valid passwords: %d\n", n_valid);

    return EXIT_SUCCESS;
}
