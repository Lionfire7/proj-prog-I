#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    int top, pos;
} DATA;

typedef struct llist {
    DATA data;
    struct llist *next;
} LIST;

typedef struct stack {
    LIST *head;
}STACK;
STACK *criar_stack(DATA ndata){
    STACK *stack = (STACK *)malloc(sizof(STACK));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}
