#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeNode.h"
#define INITIAL_SIZE 100

typedef struct {
    TreeNode** arr;
    int top;
    int cap;
} Stack;

void initialize(Stack* stack) {
    stack->arr = (TreeNode**)malloc(INITIAL_SIZE * sizeof(TreeNode*));
    stack->top = -1;
    stack->cap = INITIAL_SIZE;
    if (stack->arr == NULL)
        exit(EXIT_FAILURE);
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == stack->cap - 1;
}

void push(Stack* stack, TreeNode* node) {
    if (isFull(stack)) {
        doubleStackSize(stack);
    }
        stack->top++;
        stack->arr[stack->top] = node;
}

void doubleStackSize(Stack* stack)
{
    stack->cap *= 2;
    stack->arr = (TreeNode**)realloc(stack->arr, stack->cap * sizeof(TreeNode*));
    if (stack->arr == NULL)
        exit(EXIT_FAILURE);
}

TreeNode* pop(Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    } else {
        TreeNode* temp = stack->arr[stack->top];
        stack->top--;
        return temp;
    }
}

TreeNode* peek(Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    } else {
        return stack->arr[stack->top];
    }
}

void freeStack(Stack* stack) {
    
    for (int i = 0; i < stack->top; i++) {
        free(stack->arr[i]);
    }
    free(stack->arr);
}