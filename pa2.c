#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeNode.h"
#include "block.h"

TreeNode* buildTree(FILE* input);
void printOut1(TreeNode* root, FILE* file);
void printOut2(TreeNode* root, FILE* file);
void printOut3(TreeNode* root, FILE* file);
void printBlock(Block* b, FILE* file);
void printCut(TreeNode* node, FILE* file);
void printCoordinates(TreeNode* node, FILE* file);
void freeTree(TreeNode* root);

int main(int argc, char *argv[])
{
    if(argc != 5)
        return EXIT_FAILURE;

    FILE* input = fopen(argv[1],"r");
    if(input == NULL)
        return EXIT_FAILURE;
    
    TreeNode* root = buildTree(input);
    fclose(input);
    
    int outSuccess = 0;    
    FILE* output1 = fopen(argv[2], "w");
    if (output1 != NULL)
    {
        printOut1(root, output1);
        fclose(output1);
        outSuccess++;     
    }
    
    FILE* output2 = fopen(argv[3], "w");
    if (output2 != NULL)
    {
        
        printOut2(root, output2);
        fclose(output2);
        outSuccess++;
    }

    FILE* output3 = fopen(argv[4], "w");
    if (output3 != NULL)
    {
        // printOut3(root, output3);
        fclose(output3);
        outSuccess++;
    }

    freeTree(root);

    return outSuccess == 3 ? EXIT_SUCCESS : EXIT_FAILURE;
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

void printCoordinates(TreeNode* node, FILE* file)
{
    fprintf(file, "%d((%d,%d)(%d,%d))\n",node->data->label, node->data->width, node->data->height,-1,-1);
}

void printOut1(TreeNode* root, FILE* file)
{
    if(!root)
        return;
        
    printOut1(root->left,file);
    printOut1(root->right,file);
    if(root->cutAngle != NULL)
        fprintf(file, "%c\n", root->cutAngle);
    else if(root->data != NULL)
        printBlock(root->data, file);
}

void printOut2(TreeNode* root, FILE* file)
{
    if(!root)
        return;
    printOut2(root->left,file);
    printOut2(root->right,file);
    if(root->cutAngle != NULL)
        printCut(root, file);
    else if(root->data != NULL)
        printBlock(root->data, file);
}

void printOut3(TreeNode* root, FILE* file)
{
    if(!root)
        return;
    printOut3(root->left,file);
    printOut3(root->right,file);
    if(root->cutAngle != NULL)
        fprintf(file, "%c\n", root->cutAngle);
    else if(root->data != NULL)
        printCoordinates(root->data, file);
}

void freeTree(TreeNode* root)
{
    if(!root)
        return;
        freeTree(root->left);
        freeTree(root->right);
    if(root->data)
        free(root->data);
    free(root);
}

// TreeNode* buildTreeNR(FILE* input)
// {
//     TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
//     char line[150];
//     while(fgets(line, sizeOf(line), input) != NULL)
//     {
//         line[strcspn(line, "\n")] = '\0';

//         TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
//         if (node == NULL)
//         {
//             exit(EXIT_FAILURE);
//         }
//         if (line[0] == 'H' || line[0] == 'V')
//         {
//             root->cutAngle = line[0];
//         }
//     }
// }

TreeNode* buildTree(FILE* input)
{
    char line[256];
    if(fgets(line, sizeof(line), input) == NULL)
        return NULL;

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL)
        exit(EXIT_FAILURE);

    line[strcspn(line, "\n")] = '\0';

    if (line[0] == 'H' || line[0] == 'V')
    {
        root->data = NULL;
        root->cutAngle = line[0];
        root->left = buildTree(input);
        root->right = buildTree(input);
    }
    else
    {
        root->data = (Block*)malloc(sizeof(Block));
        if (root->data == NULL)
            exit(EXIT_FAILURE);

        sscanf(line, " %d(%d,%d)", &(root->data->label), &(root->data->width), &(root->data->height));
        root->cutAngle = NULL;
        root->left = NULL;
        root->right = NULL;
    }

    return root;
}