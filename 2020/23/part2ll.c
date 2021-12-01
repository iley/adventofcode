#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STEPS 10000000
#define CUPS  1000000

const int starting_cups = 9;
int32_t input[] = { 4, 1, 8, 9, 7, 6, 2, 3, 5 };
// int32_t input[] = { 3, 8, 9, 1, 2, 5, 4, 6, 7 }; // sample

typedef struct node_struct {
    int32_t val;
    struct node_struct* next;
} node_t;

node_t* alloc_node() {
    static node_t nodes[CUPS];
    static int next_alloc_node = 0;
    node_t* node = &nodes[next_alloc_node];
    next_alloc_node++;
    return node;
}

void print_list(node_t* head, int count) {
    node_t* node = head;
    for (int i = 0; i < count; i++) {
        printf("%d ", node->val);
        node = node->next;
    }
}

int main() {
    static node_t* node_index[CUPS+1];

    node_t* head = alloc_node();
    head->val = input[0];
    head->next = head;
    node_index[input[0]] = head;

    node_t* tail = head;

    for (int i = 1; i < CUPS; i++) {
        int32_t val;
        if (i < starting_cups) {
            val = input[i];
        } else {
            val = i + 1;
        }
        node_t* new_node = alloc_node();
        new_node->val = val;
        new_node->next = head;
        node_index[val] = new_node;
        tail->next = new_node;
        tail = new_node;
    }

    printf("first 20 elements: ");
    print_list(head, 20);
    printf("\n");

    node_t* current = head;
    for (int i = 0; i < STEPS; i++) {
        int32_t curval= current->val;

        int32_t nextval1 = current->next->val;
        int32_t nextval2 = current->next->next->val;
        int32_t nextval3 = current->next->next->next->val;

        int32_t destval = curval;
        do {
            destval--;
            if (destval == 0) destval = CUPS;
        } while (destval == nextval1 || destval == nextval2 || destval == nextval3);

        // debug logging
        // if (i % 1000 == 0) printf("move %d\n", i);

        // remove 3 elements
        node_t* removed = current->next;
        current->next = current->next->next->next->next;

        node_t* dest = node_index[destval];

        removed->next->next->next = dest->next;
        dest->next = removed;

        current = current->next;
    }

    printf("first 20 elements: ");
    print_list(head, 20);
    printf("\n");

    node_t* one;
    for (one = head; one->val != 1; one = one->next) {}

    int64_t a = one->next->val;
    int64_t b = one->next->next->val;
    printf("%"PRId64" * %"PRId64" = %"PRId64"\n", a, b, a * b);

    return EXIT_SUCCESS;
}
