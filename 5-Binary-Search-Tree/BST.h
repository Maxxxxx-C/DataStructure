//
// Created by Urala on 2022/7/14.
//

#ifndef BST_H
#define BST_H

#ifndef BST_NIL
#define BST_NIL ((void *)0)
#endif

#ifndef root
#define root right
#endif

typedef int DataType;

typedef struct BST {
    DataType key;
    struct BST *parent;
    struct BST *left;
    struct BST *right;
} BST, BST_Node;

BST *create_BST();

void free_BST(BST *);

void BST_traversal(BST *);

void BST_insert(BST *, DataType);

void BST_delete(BST *tree, BST_Node *deleting);

BST_Node *BST_search(BST *, DataType);

BST_Node *BST_minimum(BST *);

BST_Node *BST_maximum(BST *);

BST_Node *BST_predecessor(BST_Node *);

BST_Node *BST_successor(BST_Node *);

#endif //BST_H
