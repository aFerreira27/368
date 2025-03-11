#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeNode.h"
#include "block.h"
#include "stack.c"

int main(int argc, char* argv[])
{
    if(argc != 6)
        return EXIT_FAILURE;

    FILE* input = fopen(argv[1],"r");
    if(input == NULL)
        return EXIT_FAILURE;
    
    TreeNode* root = buildPostTree(input);
    fclose(input);
    
}

TreeNode* buildPostTree(FILE* input)
{
    char line[256];
    if(fgets(line, sizeof(line), input) == NULL)
        return EXIT_FAILURE;

    Stack stack;
    initialize(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top element: %d\n", peek(&stack));

    printf("Popped element: %d\n", pop(&stack));
    printf("Popped element: %d\n", pop(&stack));

    printf("Top element after pops: %d\n", peek(&stack));

    return 0;
    // TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    // if (root == NULL)
    //     exit(EXIT_FAILURE);

    // line[strcspn(line, "\n")] = '\0';

    // if (line[0] == 'H' || line[0] == 'V')
    // {
    //     root->data = NULL;
    //     root->cutAngle = line[0];
    //     root->left = buildTree(input);
    //     root->right = buildTree(input);
    // }
    // else
    // {
    //     root->data = (Block*)malloc(sizeof(Block));
    //     if (root->data == NULL)
    //         exit(EXIT_FAILURE);

    //     sscanf(line, " %d(%d,%d)", &(root->data->label), &(root->data->width), &(root->data->height));
    //     root->cutAngle = NULL;
    //     root->left = NULL;
    //     root->right = NULL;
    // }

    // return root;
}

void printOut1(TreeNode* root, FILE* file)
{
    if(root == NULL)
        return EXIT_FAILURE;
    root = rerouteTree(root, 'left');
    po1helper(root, file);
}

TreeNode* po1helper(TreeNode* root, FILE* file)
{
    if(root == NULL)
        return;
    
        if(root->cutAngle != NULL)
            fprintf(file, "%c\n", root->cutAngle);
        else if(root->data != NULL)
            printBlock(root->data, file);

        po1helper(root->left, file);
        po1helper(root->right, file);
}

void printOut2(TreeNode* root, FILE* file)
{
    
}

void printOut3(TreeNode* root, FILE* file)
{
    
}

void printOut4(TreeNode* root, FILE* file)
{
    
}

TreeNode* rerouteTree(TreeNode* root, char dir)
{
    if(root == NULL)
        return;

    if(dir == 'R')
    {
        if(root->right == NULL)
            return;
        TreeNode* formerRoot = root;
        root = root->right;
        formerRoot->right = root->left;
        root->left = formerRoot;
        root = rerouteTree(root, 'L');
    }
    else if (dir = 'L')
    {
        if(root->left == NULL)
            return;
        TreeNode* formerRoot = root;
        root = root->right;
        formerRoot->right = root->left;
        root->left = formerRoot;
    }
    
}

void printBlock(Block* b, FILE* file)
{
    fprintf(file, "%d(%d,%d)\n", b->label, b->width, b->height);
}

void printCut(TreeNode* node, FILE* file)
{
    if(node == NULL || node->left == NULL || node->right == NULL)
        return;
    TreeNode* left = node->left;
    TreeNode* right = node->right;
    if(left->data == NULL || right->data == NULL)
        return;

    if(node->cutAngle == 'H')
        fprintf(file, "%c(%d,%d)\n", node->cutAngle,left->data->width >= right->data->width ? left->data->width : right->data->width, left->data->height + right->data->height);
    if(node->cutAngle == 'V')
        fprintf(file, "%c(%d,%d)\n", node->cutAngle, left->data->width + right->data->width, left->data->height >= right->data->height ? left->data->height : right->data->height);
}

