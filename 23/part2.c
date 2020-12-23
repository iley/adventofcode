#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STEPS 10000000
#define CUPS  1000000

const int starting_cups = 9;
uint32_t input[] = { 4, 1, 8, 9, 7, 6, 2, 3, 5 };
// int32_t input[] = { 3, 8, 9, 1, 2, 5, 4, 6, 7 }; // sample

int main() {
    static int32_t ring[CUPS];

    for (int i = 0; i < CUPS; i++) {
        if (i < starting_cups) {
            ring[i] = input[i];
        } else {
            ring[i] = i+1;
        }
    }

    printf("first 20 elements: ");
    for (int i = 0; i < 20; i++) {
        printf("%d, ", ring[i]);
    }
    printf("\n");

    for (int i = 0; i < STEPS; i++) {
        int32_t curval = ring[0];

        int32_t next1 = ring[1];
        int32_t next2 = ring[2];
        int32_t next3 = ring[3];

        int32_t destval = curval;
        do {
            destval--;
            if (destval == 0) destval = CUPS;
        } while (destval == next1 || destval == next2 || destval == next3);

        // debug logging
        if (i % 1000 == 0) printf("move %d\n", i);

        // remove
        int i;
        for (i = 1; i < CUPS-3; i++) {
            ring[i] = ring[i+3];
            if (ring[i] == destval) break;
        }

        // insert
        ring[i+1] = next1;
        ring[i+2] = next2;
        ring[i+3] = next3;

        // rotatle left
        int32_t head = ring[0];
        for (int i = 0; i < CUPS-1; i++) {
            ring[i] = ring[i+1];
        }
        ring[CUPS-1] = head;
    }

    printf("---\n");
    printf("first 20 elements: ");
    for (int i = 0; i < 20; i++) {
        printf("%d, ", ring[i]);
    }
    printf("\n");

    for (int i = 0; i < CUPS; i++) {
        if ( ring[i] == 1) {
            int64_t a = ring[(i+1) % CUPS];
            int64_t b = ring[(i+2) % CUPS];
            printf("%ld * %ld = %ld\n", a, b, a * b);
            break;
        }
    }

    return EXIT_SUCCESS;
}
