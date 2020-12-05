#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int max_items = 1000;

int read_items(int items[]) {
    size_t n_items = 0;
    while (true) {
        int item;
        if (scanf("%d", &item) != 1) {
            break;
        }
        items[n_items] = item;
        n_items++;
    }
    return n_items;
}

bool find_sum(int items[], size_t n_items, int target, int* out_a, int* out_b, int* out_c) {
    for (size_t i = 0; i < n_items; i++) {
        for (size_t j = 0; j < i; j++) {
            for (size_t k = 0; k < i; k++) {
                if (items[i] + items[j] + items[k] == target) {
                    *out_a = items[i];
                    *out_b = items[j];
                    *out_c = items[k];
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    static int items[max_items];

    size_t n_items = read_items(items);
    printf("read %zu items\n", n_items);

    const int target = 2020;
    int a, b, c;
    if (find_sum(items, n_items, target, &a, &b, &c)) {
        printf("found solution: %d + %d + %d = %d\n", a, b, c, target);
        printf("%d * %d * %d = %d\n", a, b, c, a * b * c);
    } else {
        printf("found no solution\n");
    }

    return EXIT_SUCCESS;
}
