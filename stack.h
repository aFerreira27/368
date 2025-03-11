#ifndef STACK_H
#define STACK_H

#include "treeNode.h"

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

void initialize(Stack* stack);
int isEmpty(Stack* stack);
int isFull(Stack* stack);
void doubleStackSize(Stack* stack);
void push(Stack* stack, TreeNode* node);
TreeNode* pop(Stack* stack);
TreeNode* peek(Stack* stack);
void freeStack(Stack* stack);

#endif