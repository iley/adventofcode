#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// int64_t public_keys[] = { 5764801, 17807724 }; // sample
int64_t public_keys[] = { 14012298, 74241 }; // input
int64_t seed = 7;

int64_t crack_loop_size(int64_t pubkey) {
    int64_t val = 1;
    int64_t loop_size = 0;
    while ( val != pubkey ) {
        val = (val * seed) % 20201227;
        loop_size++;
    }
    return loop_size;
}

int64_t transform(int64_t subj, int64_t loop_size) {
    int64_t val = 1;
    for (int64_t i = 0; i < loop_size; i++) {
        val = (val * subj) % 20201227;
    }
    return val;
}

int main() {
    int64_t loop_size0 = crack_loop_size(public_keys[0]);
    printf("loop size #1 is %"PRId64"\n", loop_size0);

    int64_t loop_size1 = crack_loop_size(public_keys[1]);
    printf("loop size #2 is %"PRId64"\n", loop_size1);

    int64_t key = transform(public_keys[1], loop_size0);
    printf("key is %"PRId64"\n", key);

    return EXIT_SUCCESS;
}
