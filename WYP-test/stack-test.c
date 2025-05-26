#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    int top, pos;
} DATA;

typedef struct llist {
    DATA data;
    struct llist* next;
} llist;

typedef struct stack {
    llist* head;
}STACK;

int isEmpty(STACK* stack) {
  
    return stack->head == NULL;
}

STACK *criar_stack(DATA ndata){
    STACK *stack = (STACK *)malloc(sizeof(STACK));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    llist *new_node = (llist *)malloc(sizeof(llist));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = ndata;
    new_node->next = NULL;
    stack->head = new_node;
    return stack;
}

void initializeStack(STACK* stack) { stack->head = NULL; }

void push(STACK* stack, DATA ndata){
  
    llist* new_node = (llist*)malloc(sizeof(llist));

    new_node->data = ndata;
    new_node->next = stack->head;
    stack->head = new_node;

}

DATA peek(STACK* stack) {
  
    if (!isEmpty(stack))
        return stack->head->data;
    else {
        printf("\nStack is empty");
        return (DATA){-1, -1};
    }
}

int main() {

    STACK stack;
    initializeStack(&stack);

    push(&stack, (DATA){11, 11});
    push(&stack, (DATA){22, 22});
    push(&stack, (DATA){33, 33});
    push(&stack, (DATA){44, 44});

    printf("Top element is %d, %d\n", peek(&stack).top, peek(&stack).pos);

    printf("Top element is %d, %d\n ", peek(&stack));

    return 0;
}