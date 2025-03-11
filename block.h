#ifndef BLOCK_H
#define BLOCK_H

struct block;
typedef struct block Block;

struct block {
    int label;
    long width;
    long height;
};

#endif