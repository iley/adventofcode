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

bool find_sum(int items[], size_t n_items, int target, int* out_a, int* out_b) {
    for (size_t i = 1; i < n_items; i++) {
        for (size_t j = 0; j < i; j++) {
            if (items[i] + items[j] == target) {
                *out_a = items[i];
                *out_b = items[j];
                return true;
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
    int a, b;
    if (find_sum(items, n_items, target, &a, &b)) {
        printf("found solution: %d + %d = %d\n", a, b, target);
        printf("%d * %d = %d\n", a, b, a * b);
    } else {
        printf("found no solution\n");
    }

    return EXIT_SUCCESS;
}
