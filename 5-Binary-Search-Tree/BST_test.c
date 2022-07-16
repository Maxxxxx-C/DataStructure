//
// Created by Urala on 2022/7/14.
//

#include "stdio.h"
#include "BST.h"

static void insert_test(){
    printf("\n~~insert testing~~\n");
    BST *tree = create_BST();
    BST_insert(tree, 10);
    BST_insert(tree, 9);
    BST_insert(tree, 15);
    BST_insert(tree, 6);
    BST_insert(tree, 3);
    BST_insert(tree, 4);
    BST_insert(tree, 12);
    BST_insert(tree, 19);
    BST_insert(tree, 8);
    BST_insert(tree, 17);
    BST_traversal(tree);
    free_BST(tree);
    printf("\n");
}

static void delete_test(){
    printf("\n~~delete testing~~\n");
    BST *tree = create_BST();
    BST_insert(tree, 10);
    BST_insert(tree, 9);
    BST_insert(tree, 15);
    BST_insert(tree, 6);
    BST_insert(tree, 3);
    BST_insert(tree, 4);
    BST_insert(tree, 12);
    BST_insert(tree, 19);
    BST_insert(tree, 7);
    BST_insert(tree, 8);
    BST_insert(tree, 17);
    printf("\nbefore deleting:\n");
    BST_traversal(tree);
    printf("\n%d\n", tree->root->key);

    printf("\ndelete the root:\n");
    BST_delete(tree, BST_search(tree, 10));
    BST_traversal(tree);
    printf("\n%d\n", tree->root->key);

    printf("\ndelete 7, 15:\n");
    BST_delete(tree, BST_search(tree, 7));
    BST_delete(tree, BST_search(tree, 15));
    BST_traversal(tree);

    free_BST(tree);
    printf("\n");
}

int main() {
    insert_test();
    delete_test();
    return 0;
}