//
// Created by Urala on 2022/7/14.
//

#ifndef DATASTRUCTURE_RBT_H
#define DATASTRUCTURE_RBT_H

#ifndef RBT_NIL
#define RBT_NIL ((void *)0)
#endif

#ifndef root
#define root right
#endif

typedef int DataType;

typedef enum Color{
    BLACK,
    RED
} Color;

typedef struct RBT{
    DataType key;
    Color color;
    struct RBT *parent;
    struct RBT *left;
    struct RBT *right;
} RBT, RBT_Node;

RBT *create_RBT();

void free_RBT(RBT *tree);

void RBT_traversal(RBT *tree);

void RBT_insert(RBT *tree, DataType data);

void RBT_delete(RBT *tree, RBT_Node *deleting);

RBT_Node *RBT_search(RBT *tree, DataType searching);

RBT_Node *RBT_minimum(RBT *tree);

RBT_Node *RBT_maximum(RBT *tree);

RBT_Node *RBT_predecessor(RBT_Node *node);

RBT_Node *RBT_successor(RBT_Node *node);

#endif //DATASTRUCTURE_RBT_H
