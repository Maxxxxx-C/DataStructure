//
// Created by Urala on 2022/7/14.
//

#include "stdio.h"
#include "stdlib.h"
#include "RBT.h"

static RBT_Node nil_node = {0, BLACK, RBT_NIL, RBT_NIL, RBT_NIL};

static RBT_Node *nil = &nil_node;

RBT *create_RBT() {
    RBT *new_tree = malloc(sizeof(RBT));
    new_tree->key = 0;
    new_tree->color = BLACK;
    new_tree->parent = RBT_NIL;
    new_tree->left = RBT_NIL;
    new_tree->right = RBT_NIL;
    return new_tree;
}

static char *get_color(RBT_Node *node) {
    switch (node->color) {
        case RED:
            return "RED";
        case BLACK:
        default:
            return "BLACK";
    }
}

static void inorder_traversal(RBT *node) {
    if (node != nil) {
        if (node->left != nil) {
            inorder_traversal(node->left);
        }
        printf("%d\t%s\n", node->key, get_color(node));
        if (node->right != nil) {
            inorder_traversal(node->right);
        }
    }
}

void RBT_traversal(RBT *tree) {
    inorder_traversal(tree->root);
}

RBT_Node *RBT_search(RBT *tree, DataType searching) {
    RBT_Node *patrol = tree->root;
    while (patrol != nil) {
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

static RBT_Node *minimum(RBT_Node *node) {
    RBT_Node *patrol = node;
    while (patrol->left != nil) {
        patrol = patrol->left;
    }
    return patrol;
}

RBT_Node *RBT_minimum(RBT *tree) {
    return minimum(tree->root);
}

static RBT_Node *maximum(RBT_Node *node) {
    RBT_Node *patrol = node;
    while (patrol->right != nil) {
        patrol = patrol->right;
    }
    return patrol;
}

RBT_Node *RBT_maximum(RBT *tree) {
    return maximum(tree->root);
}

RBT_Node *RBT_predecessor(RBT_Node *node) {
    if (node != nil) {
        if (node->left != nil) {
            return maximum(node->left);
        } else {
            RBT_Node *patrol = node;
            while (patrol->parent != nil && patrol == patrol->parent->left) {
                patrol = patrol->parent;
            }
            return patrol->parent;
        }
    }
    return node;
}

RBT_Node *RBT_successor(RBT_Node *node) {
    if (node != nil) {
        if (node->right != nil) {
            return minimum(node->left);
        } else {
            RBT_Node *patrol = node;
            while (patrol->parent != nil && patrol == patrol->parent->right) {
                patrol = patrol->parent;
            }
            return patrol->parent;
        }
    }
    return node;
}

static void replace(RBT *tree, RBT_Node *replaced, RBT_Node *another) {
    if (replaced == tree->root) {
        tree->root = another;
    } else if (replaced == replaced->parent->left) {
        replaced->parent->left = another;
    } else {
        replaced->parent->right = another;
    }
    another->parent = replaced->parent;
}

static void left_rotate(RBT *tree, RBT_Node *pivot) {
    RBT_Node *rotated = pivot->right;

    pivot->right = rotated->left;
    if (rotated->left != nil) {
        rotated->left->parent = pivot;
    }

    rotated->parent = pivot->parent;
    if (pivot == tree->root) {
        tree->root = rotated;
    } else if (pivot == pivot->parent->left) {
        pivot->parent->left = rotated;
    } else {
        pivot->parent->right = rotated;
    }

    pivot->parent = rotated;
    rotated->left = pivot;
}

static void right_rotate(RBT *tree, RBT_Node *pivot) {
    RBT_Node *rotated = pivot->left;

    pivot->left = rotated->right;
    if (rotated->right != nil) {
        rotated->right->parent = pivot;
    }

    rotated->parent = pivot->parent;
    if (pivot == tree->root) {
        tree->root = rotated;
    } else if (pivot == pivot->parent->left) {
        pivot->parent->left = rotated;
    } else {
        pivot->parent->right = rotated;
    }

    pivot->parent = rotated;
    rotated->right = pivot;
}

static RBT_Node *create_node(DataType data) {
    RBT_Node *new_node = malloc(sizeof(RBT_Node));
    new_node->key = data;
    new_node->color = RED;
    new_node->parent = nil;
    new_node->left = nil;
    new_node->right = nil;
    return new_node;
}

static void insert_fixup(RBT *tree, RBT_Node *node) {
    RBT_Node *patrol = node;
    while (patrol->parent->color == RED) {
        if (patrol->parent == patrol->parent->parent->left) {
            RBT_Node *patrol_parent_sibling = patrol->parent->parent->right;
            if (patrol_parent_sibling->color == RED) {
                patrol->parent->color = BLACK;
                patrol_parent_sibling->color = BLACK;
                patrol->parent->parent->color = RED;
                patrol = patrol->parent->parent;
            } else {
                if (patrol == patrol->parent->right) {
                    patrol = patrol->parent;
                    left_rotate(tree, patrol);
                }
                patrol->parent->color = BLACK;
                patrol->parent->parent->color = RED;
                right_rotate(tree, patrol->parent->parent);
            }
        } else {
            RBT_Node *patrol_parent_sibling = patrol->parent->parent->left;
            if (patrol_parent_sibling->color == RED) {
                patrol->parent->color = BLACK;
                patrol_parent_sibling->color = BLACK;
                patrol->parent->parent->color = RED;
                patrol = patrol->parent->parent;
            } else {
                if (patrol == patrol->parent->left) {
                    patrol = patrol->parent;
                    right_rotate(tree, patrol);
                }
                patrol->parent->color = BLACK;
                patrol->parent->parent->color = RED;
                left_rotate(tree, patrol->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void RBT_insert(RBT *tree, DataType data) {
    RBT_Node *new_node = create_node(data);
    if (tree->root == RBT_NIL) {
        tree->root = new_node;
        new_node->color = BLACK;
    } else {
        RBT_Node *patrol = tree->root;
        RBT_Node *patrol_parent;
        while (patrol != nil) {
            if (data <= patrol->key) {
                patrol_parent = patrol;
                patrol = patrol->left;
            } else {
                patrol_parent = patrol;
                patrol = patrol->right;
            }
        }
        new_node->parent = patrol_parent;
        if (data <= patrol_parent->key) {
            patrol_parent->left = new_node;
        } else {
            patrol_parent->right = new_node;
        }
        insert_fixup(tree, new_node);
    }
}

static void delete_fixup(RBT *tree, RBT_Node *node) {
    RBT_Node *sibling;
    while (node != tree->root && node->color == BLACK) {
        if (node == node->parent->left) {
            sibling = node->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                sibling->parent->color = RED;
                left_rotate(tree, sibling->parent);
            } else {
                if (sibling->right->color == BLACK) {
                    if (sibling->left->color == BLACK) {
                        sibling->color = RED;
                        node = node->parent;
                    } else {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        right_rotate(tree, sibling);
                    }
                } else {
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    left_rotate(tree, sibling->parent);
                    node = tree->root;
                }
            }
        } else {
            sibling = node->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                sibling->parent->color = RED;
                right_rotate(tree, sibling->parent);
            } else {
                if (sibling->left->color == BLACK) {
                    if (sibling->right->color == BLACK) {
                        sibling->color = RED;
                        node = node->parent;
                    } else {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        left_rotate(tree, sibling);
                    }
                } else {
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    right_rotate(tree, sibling->parent);
                    node = tree->root;
                }
            }
        }
    }
    node->color = BLACK;
}

void RBT_delete(RBT *tree, RBT_Node *deleting) {
    if (deleting != nil) {
        RBT_Node *key_node;
        Color original_color = deleting->color;
        if (deleting->left == nil) {
            key_node = deleting->right;
            replace(tree, deleting, deleting->right);
        } else if (deleting->right == nil) {
            key_node = deleting->left;
            replace(tree, deleting, deleting->left);
        } else {
            RBT_Node *successor = minimum(deleting->right);
            original_color = successor->color;
            key_node = successor->right;
            if (successor->parent == deleting) {
                key_node->parent = successor;
            } else {
                replace(tree, successor, successor->right);
                successor->right = deleting->right;
                successor->right->parent = successor;
            }
            replace(tree, deleting, successor);
            successor->left = deleting->left;
            successor->left->parent = successor;
            successor->color = deleting->color;
        }
        free(deleting);
        if (original_color == BLACK) {
            delete_fixup(tree, key_node);
        }
    }
}