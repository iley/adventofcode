#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int cups = 9;
// int8_t input[] = { 3, 8, 9, 1, 2, 5, 4, 6, 7 }; // sample
int8_t input[] = { 4, 1, 8, 9, 7, 6, 2, 3, 5 };

int main() {
    const int steps = 100;

    for (int i = 0; i < steps; i++) {
        int8_t curval = input[0];

        int8_t next1 = input[1];
        int8_t next2 = input[2];
        int8_t next3 = input[3];

        int8_t destval = curval;
        do {
            destval--;
            if (destval == 0) destval = cups;
        } while (destval == next1 || destval == next2 || destval == next3);

        // debug logging
        printf("move %d\n", i+1);
        for (int i = 0; i < cups; i++) {
            printf("%d ", input[i]);
        }
        printf("\n");
        printf("pick up: %d, %d, %d\n", next1, next2, next3);
        printf("dest: %d\n", destval);
        printf("\n");
        // end debug logging

        // remove
        int i;
        for (i = 1; i < steps-3; i++) {
            input[i] = input[i+3];
            if (input[i] == destval) break;
        }

        // insert
        input[i+1] = next1;
        input[i+2] = next2;
        input[i+3] = next3;

        // rotatle left
        int8_t head = input[0];
        for (int i = 0; i < cups-1; i++) {
            input[i] = input[i+1];
        }
        input[cups-1] = head;
    }

    printf("---\n");
    for (int i = 0; i < cups; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
