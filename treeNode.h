#ifndef TREENODE_H
#define TREENODE_H

#include "block.h"

struct treeNode;
typedef struct treeNode TreeNode;

struct treeNode
{
    Block* data;
    struct treeNode* left;
    struct treeNode* right;
    char cutAngle;
};

TreeNode* buildPostTree(FILE* input);
TreeNode* buildPreTree(FILE* input);

#endif