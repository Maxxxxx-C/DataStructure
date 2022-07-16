//
// Created by Urala on 2022/7/14.
//

#include "stdio.h"
#include "stdlib.h"
#include "BST.h"

static BST_Node *create_node(DataType data) {
    BST_Node *new_node = malloc(sizeof(BST_Node));
    new_node->key = data;
    new_node->parent = BST_NIL;
    new_node->left = BST_NIL;
    new_node->right = BST_NIL;
    return new_node;
}

BST *create_BST() {
    BST *new_tree = malloc(sizeof(BST));
    new_tree->key = 0;
    new_tree->parent = BST_NIL;
    new_tree->left = BST_NIL;
    new_tree->right = BST_NIL;
    return new_tree;
}

static void inorder_traversal(BST_Node *node) {
    if (node != BST_NIL) {
        inorder_traversal(node->left);
        printf("%d, ", node->key);
        inorder_traversal(node->right);
    }
}

void BST_traversal(BST *tree) {
    inorder_traversal(tree->root);
}

static void postorder_free(BST_Node *node) {
    if (node != BST_NIL) {
        postorder_free(node->left);
        postorder_free(node->right);
        if (node->parent != BST_NIL) {
            if (node == node->parent->left) {
                node->parent->left = BST_NIL;
            } else if (node == node->parent->right) {
                node->parent->right = BST_NIL;
            }
        }
        free(node);
    }
}

void free_BST(BST *tree) {
    postorder_free(tree->root);
    free(tree);
}

BST_Node *BST_search(BST *tree, DataType searching) {
    BST_Node *patrol = tree->root;
    while (patrol != BST_NIL) {
        if (searching == patrol->key) {
            break;
        } else if (searching < patrol->key) {
            patrol = patrol->left;
        } else {
            patrol = patrol->right;
        }
    }
    return patrol;
}

static void replace(BST *tree, BST_Node *replaced, BST_Node *another) {
    if (replaced == tree->root) {
        tree->root = another;
    } else if (replaced == replaced->parent->left) {
        replaced->parent->left = another;
    } else {
        replaced->parent->right = another;
    }
    if (another != BST_NIL) {
        another->parent = replaced->parent;
    }
}

static BST_Node *minimum(BST_Node *node) {
    BST_Node *patrol = node;
    while (patrol->left != BST_NIL) {
        patrol = patrol->left;
    }
    return patrol;
}

BST_Node *BST_minimum(BST *tree) {
    return minimum(tree->root);
}

static BST_Node *maximum(BST_Node *node) {
    BST_Node *patrol = node;
    while (patrol->right != BST_NIL) {
        patrol = patrol->right;
    }
    return patrol;
}

BST_Node *BST_maximum(BST *tree) {
    return maximum(tree->root);
}

BST_Node *BST_predecessor(BST_Node *node) {
    if (node->left != BST_NIL) {
        return maximum(node->left);
    } else {
        BST_Node *patrol = node;
        while (patrol->parent != BST_NIL && patrol == patrol->parent->left) {
            patrol = patrol->parent;
        }
        return patrol->parent;
    }
}

BST_Node *BST_successor(BST_Node *node) {
    if (node->left != BST_NIL) {
        return minimum(node->right);
    } else {
        BST_Node *patrol = node;
        while (patrol->parent != BST_NIL && patrol == patrol->parent->right) {
            patrol = patrol->parent;
        }
        return patrol->parent;
    }
}

void BST_insert(BST *tree, DataType data) {
    BST_Node *node = create_node(data);
    if (tree->root == BST_NIL) {
        tree->root = node;
    } else {
        BST_Node *patrol = tree->root;
        BST_Node *patrol_parent;
        while (patrol != BST_NIL) {
            if (data <= patrol->key) {
                patrol_parent = patrol;
                patrol = patrol->left;
            } else {
                patrol_parent = patrol;
                patrol = patrol->right;
            }
        }
        node->parent = patrol_parent;
        if (data <= patrol_parent->key) {
            patrol_parent->left = node;
        } else {
            patrol_parent->right = node;
        }
    }
}

void BST_delete(BST *tree, BST_Node *deleting) {
    if (deleting != BST_NIL) {
        if (deleting->left == BST_NIL) {
            replace(tree, deleting, deleting->right);
            free(deleting);
        } else if (deleting->right == BST_NIL) {
            replace(tree, deleting, deleting->left);
            free(deleting);
        } else {
            BST_Node *successor = minimum(deleting->right);
            if (successor->parent == deleting) {
                replace(tree, deleting, successor);
                successor->left = deleting->left;
                deleting->left->parent = successor;
                free(deleting);
            } else {
                replace(tree, successor, successor->right);
                replace(tree, deleting, successor);
                successor->left = deleting->left;
                deleting->left->parent = successor;
                successor->right = deleting->right;
                deleting->right->parent = successor;
                free(deleting);
            }
        }
    }
}