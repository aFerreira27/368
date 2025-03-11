#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeNode.h"
#include "block.h"
#include "stack.h"

TreeNode* rerouteTree(TreeNode* root, char dir);
TreeNode* pohelper(TreeNode* root, FILE* file);

TreeNode* buildPostTree(FILE* input)
{
    char line[256];
    Stack stack;
    initialize(&stack);

    while(fgets(line, sizeof(line), input) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
        if (root == NULL)
            exit(EXIT_FAILURE);

        if (line[0] == 'H' || line[0] == 'V')
        {
            root->data = NULL;
            root->cutAngle = line[0];
            root->left = NULL;
            root->right = NULL;
        }

        else
        {
            root->data = (Block*)malloc(sizeof(Block));
            if (root->data == NULL)
                exit(EXIT_FAILURE);

            sscanf(line, " %d(%d,%d)", &(root->data->label), &(root->data->width), &(root->data->height));
            root->cutAngle = '\0';
            root->left = NULL;
            root->right = NULL;
        }

        push(&stack, root);

        if(peek(&stack)->cutAngle != '\0')
        {
            TreeNode* temp = pop(&stack);
            temp->right = pop(&stack);
            temp->left = pop(&stack);
            push(&stack, temp);
        }
    }

    if(isEmpty(&stack))
    {
        return NULL;
    }

    TreeNode* temp = pop(&stack);
    freeStack(&stack);
    return temp;
}

void freeTree(TreeNode* root)
{
    if(root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    if(root->data)
        free(root->data);

    free(root);
}

void printOut1(TreeNode* root, FILE* file)
{
    if(root == NULL)
        return;
    // root = rerouteTree(root, 'R');
    pohelper(root, file);
}

TreeNode* pohelper(TreeNode* root, FILE* file)
{
    if(root == NULL)
        return;
    
        if(root->cutAngle != '\0')
            fprintf(file, "%c\n", root->cutAngle);
        else if(root->data != NULL)
            printBlock(root->data, file);

        pohelper(root->left, file);
        pohelper(root->right, file);
        return root;
}

void printOut2(TreeNode* root, FILE* file)
{
    if(root == NULL)
        return;
    // root = rerouteTree(root, 'R');
    pohelper(root, file);
}

void printOut3(TreeNode* root, FILE* file)
{
    if(root == NULL)
        return;
    // root = rerouteTree(root, 'R');
    pohelper(root, file);
}

void printOut4(TreeNode* root, FILE* file)
{
    if(root == NULL)
        return;
    // root = rerouteTree(root, 'R');
    pohelper(root, file);
}

TreeNode* rerouteTree(TreeNode* root, char dir)
{
    if(root == NULL)
        return NULL;

    TreeNode* formerRoot = root;

    if(dir == 'R')
    {
        if(root->right == NULL)
            return NULL;
        root = root->right;
        formerRoot->right = root->right;
        root->right = formerRoot;
        root = rerouteTree(root, 'L');
    }
    else if (dir == 'L')
    {
        if(root->left == NULL)
            return NULL;
        root = root->left;
        formerRoot->right = root->right;
        root->right = formerRoot;
        root = rerouteTree(root, 'R');
    }
    
    return root;
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

int main(int argc, char* argv[])
{
    if(argc != 6)
        return EXIT_FAILURE;

    FILE* input = fopen(argv[1],"r");
    if(input == NULL)
        return EXIT_FAILURE;
    
    TreeNode* root = buildPostTree(input);
    fclose(input);
    

    FILE* op1 = fopen(argv[2],"w");
    if(op1 == NULL)
        return EXIT_FAILURE;
    printOut1(root, op1);
    fclose(op1);

    FILE* op2 = fopen(argv[3],"w");
    if(op2 == NULL)
        return EXIT_FAILURE;
    printOut2(root, op2);
    fclose(op2);

    FILE* op3 = fopen(argv[4],"w");
    if(op3 == NULL)
        return EXIT_FAILURE;
    printOut3(root, op3);
    fclose(op3);

    FILE* op4 = fopen(argv[5],"w");
    if(op4 == NULL)
        return EXIT_FAILURE;
    printOut4(root, op4);
    fclose(op4);

    freeTree(root);
}