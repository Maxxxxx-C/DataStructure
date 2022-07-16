//
// Created by Urala on 2022/7/14.
//

#include "stdio.h"
#include "RBT.h"

static void insert_test(){
    printf("\n~~insert testing~~\n");
    RBT *tree = create_RBT();
    RBT_insert(tree, 10);
    RBT_insert(tree, 9);
    RBT_insert(tree, 6);
    RBT_insert(tree, 15);
    RBT_insert(tree, 3);
    RBT_insert(tree, 4);
    RBT_insert(tree, 12);
    RBT_insert(tree, 19);
    RBT_insert(tree, 8);
    RBT_insert(tree, 17);
    RBT_traversal(tree);
    printf("\n");
}

static void delete_test(){
    printf("\n~~delete testing~~\n");
    RBT *tree = create_RBT();
    RBT_insert(tree, 41);
    RBT_insert(tree, 38);
    RBT_insert(tree, 31);
    RBT_insert(tree, 12);
    RBT_insert(tree, 19);
    RBT_insert(tree, 8);
    RBT_traversal(tree);
    printf("~~delete 8~~\n");
    RBT_delete(tree, RBT_search(tree, 8));
    RBT_traversal(tree);
    printf("~~delete 12~~\n");
    RBT_delete(tree, RBT_search(tree, 12));
    RBT_traversal(tree);
    printf("~~delete 19~~\n");
    RBT_delete(tree, RBT_search(tree, 19));
    RBT_traversal(tree);
    printf("~~delete 31~~\n");
    RBT_delete(tree, RBT_search(tree, 31));
    RBT_traversal(tree);
    printf("~~delete 38~~\n");
    RBT_delete(tree, RBT_search(tree, 38));
    RBT_traversal(tree);
    printf("~~delete 41~~\n");
    RBT_delete(tree, RBT_search(tree, 41));
    RBT_traversal(tree);
}

int main(){
    delete_test();
    return 0;
}
