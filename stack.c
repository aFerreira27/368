#include <stdio.h>
#include <stdlib.h>

#include "treeNode.h"

#define MAX_SIZE 100

typedef struct {
    TreeNode* arr[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int value) {
    if (isFull(stack)) {
        doubleStackSize(stack);
    }
        stack->top++;
        stack->arr[stack->top] = value;
}

void doubleStackSize(Stack* stack)
{
    TreeNode* temp[sizeof(stack->arr) / sizeof(stack->arr[0]) * 2];
    memcpy(temp, *stack->arr, sizeof(*stack->arr));
    *stack->arr = temp;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    } else {
        int value = stack->arr[stack->top];
        stack->top--;
        return value;
    }
}

int peek(Stack* stack) {
    if (isEmpty(stack)) {
        // printf("Stack is empty\n");
        return -1;
    } else {
        return stack->arr[stack->top];
    }
}