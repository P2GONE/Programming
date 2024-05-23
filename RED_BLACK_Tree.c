#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node* left, * right, * parent;
} Node;

typedef struct {
    Node* root;
    Node* NIL;
} RedBlackTree;

char MENU() {
    char input_menu;
    printf("Welcome to my RED_BLACK_TREE!!\n");
    printf("You can use my program through the command. The description of the button is as follows\n");
    printf("1. search : [s] \n2. minimum : [min]\n3. maximum : [max]\n4. next value : [n]\n5. previous value : [p]\n6. insertion : [i]\n7. delete : [d]\n8. terminate : [t]\n");
    scanf("%c", &input_menu);
    return input_menu;
}

void INORDER_TRAVERSAL(RedBlackTree* Tree, Node* x) {
    if (x != Tree->NIL) {
        INORDER_TRAVERSAL(Tree, x->left);
        printf("%d ", x->key);
        INORDER_TRAVERSAL(Tree, x->right);
    }
}

Node* CREATE_RED_BLACK_TREE_NODE(int key, Color color, Node* NIL) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = color;
    node->left = node->right = node->parent = NIL;
    return node;
}

RedBlackTree* CREATE_RED_BLACK_TREE() {
    RedBlackTree* Tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    Tree->NIL = CREATE_RED_BLACK_TREE_NODE(0, BLACK, NULL);
    Tree->root = Tree->NIL;
    return Tree;
}

void LEFT_ROTATE(RedBlackTree* Tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != Tree->NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == Tree->NIL) {
        Tree->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RED_BLACK_TREE_FIXUP(RedBlackTree* Tree, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else if (z == z->parent) {
                z = z->parent;
                LEFT_ROTATE(Tree, z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            RIGHT_ROTATE(Tree, z->parent->parent);
        }
        else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RIGHT_ROTATE(Tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LEFT_ROTATE(Tree, z->parent->parent);
            }
        }
    }
    Tree->root->color = BLACK;
}

void RIGHT_ROTATE(RedBlackTree* Tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != Tree->NIL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == Tree->NIL) {
        Tree->root = x;
    }
    else if (y == y->parent->right) {
        y->parent->right = x;
    }
    else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}
void RED_BLACK_TREE_INSERT(RedBlackTree* Tree, Node* z) {
    Node* y = Tree->NIL;
    Node* x = Tree->root;
    while (x != Tree->NIL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == Tree->NIL) {
        Tree->root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = Tree->NIL;
    z->right = Tree->NIL;
    z->color = RED;
    RED_BLACK_TREE_FIXUP(Tree, z);
}

void RED_BLACK_TREE_TRANSPLANT(RedBlackTree* Tree, Node* u, Node* v) {
    if (u->parent == Tree->NIL) {
        Tree->root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

Node* RED_BLACK_TREE_MAXIMUM(RedBlackTree* Tree, Node* x) {
    while (x->right != Tree->NIL) {
        x = x->right;
    }
    return x;
}

Node* RED_BLACK_TREE_MINIMUM(RedBlackTree* Tree, Node* x) {
    while (x->left != Tree->NIL) {
        x = x->left;
    }
    return x;
}

Node* RED_BLACK_TREE_PREDECESSOR(RedBlackTree* Tree, Node* x) {
    if (x->left != Tree->NIL) {
        return RED_BLACK_TREE_MAXIMUM(Tree, x->left);
    }
    Node* y = x->parent;
    while (y != Tree->NIL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

void RED_BLACK_TREE_DELETE_FIXUP(RedBlackTree* Tree, Node* x) {
    while (x != Tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                LEFT_ROTATE(Tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                RIGHT_ROTATE(Tree, w);
                w = x->right;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            LEFT_ROTATE(Tree, x->parent);
            x = Tree->root;
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                LEFT_ROTATE(Tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                RIGHT_ROTATE(Tree, w);
                w = x->right;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            LEFT_ROTATE(Tree, x->parent);
            x = Tree->root;

        }

    }
    x->color = BLACK;
}

void RED_BLACK_TREE_DELETE(RedBlackTree* Tree, Node* z) {
    Node* y = z;
    Node* x;
    Color y_original_color = y->color;
    if (z->left == Tree->NIL) {
        x = z->right;
        RED_BLACK_TREE_TRANSPLANT(Tree, z, z->right);
    }
    else if (z->right == Tree->NIL) {
        x = z->left;
        RED_BLACK_TREE_TRANSPLANT(Tree, z, z->left);
    }
    else {
        y = RED_BLACK_TREE_MINIMUM(Tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            RED_BLACK_TREE_TRANSPLANT(Tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RED_BLACK_TREE_TRANSPLANT(Tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;

    }
    if (y_original_color == BLACK) {
        RED_BLACK_TREE_DELETE_FIXUP(Tree, x);
    }
}

void INSERT_KEY(RedBlackTree* Tree) {
    int key;
    printf("Enter key to insert: ");
    scanf("%d", &key);
    Node* newNode = CREATE_RED_BLACK_TREE_NODE(key, RED, Tree->NIL);
    RED_BLACK_TREE_INSERT(Tree, newNode);
    printf("Key %d inserted.\n", key);
}

void DELETE_KEY(RedBlackTree* Tree) {
    int key;
    printf("Enter key to delete: ");
    scanf("%d", &key);
    Node* current = Tree->root;
    while (current != Tree->NIL && current->key != key) {
        if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    if (current != Tree->NIL) {
        RED_BLACK_TREE_DELETE(Tree, current);
        printf("Key %d deleted.\n", key);
    }
    else {
        printf("Key %d not found.\n", key);
    }
}

int main(int argc, char* argv[]) {
    RedBlackTree* Tree = CREATE_RED_BLACK_TREE();
    while (1) {
        char input_menu = MENU();
        getchar();
        if (input_menu == 'i') {
            INSERT_KEY(Tree);
        }
        else if (input_menu == 'd') {
            DELETE_KEY(Tree);
        }
        else if (input_menu == 's') {
            //중위 순회 
            printf("Inorder traversal of the tree:\n");
            INORDER_TRAVERSAL(Tree, Tree->root);
            printf("\n");
        }
        else if (input_menu == 'min') {
            Node* minNode = RED_BLACK_TREE_MINIMUM(Tree, Tree->root);
            if (minNode != Tree->NIL) {
                printf("Minimum key is: %d\n", minNode->key);
            }
            else {
                printf("Tree is empty.\n");
            }
        }
        else if (input_menu == 'max') {
            Node* maxNode = RED_BLACK_TREE_MAXIMUM(Tree, Tree->root);
            if (maxNode != Tree->NIL) {
                printf("Maximum key is: %d\n", maxNode->key);
            }
            else {
                printf("Tree is empty.\n");
            }
        }
        else if (input_menu == 'n') {
            int key;
            printf("Enter key to find the next value: ");
            scanf("%d", &key);
            getchar();
            Node* current = Tree->root;
            while (current != Tree->NIL && current->key != key) {
                if (key < current->key) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            if (current != Tree->NIL) {
                Node* successor = RED_BLACK_TREE_SUCCESSOR(Tree, current);
                if (successor != Tree->NIL) {
                    printf("Next value after key %d is: %d\n", key, successor->key);
                }
                else {
                    printf("No next value found.\n");
                }
            }
            else {
                printf("Key %d not found.\n", key);
            }
        }
        else if (input_menu == 'p') {
            int key;
            printf("Enter key to find the previous value: ");
            scanf("%d", &key);
            getchar();
            Node* current = Tree->root;
            while (current != Tree->NIL && current->key != key) {
                if (key < current->key) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            if (current != Tree->NIL) {
                Node* predecessor = RED_BLACK_TREE_PREDECESSOR(Tree, current);
                if (predecessor != Tree->NIL) {
                    printf("Previous value before key %d is: %d\n", key, predecessor->key);
                }
                else {
                    printf("No previous value found.\n");
                }
            }
            else {
                printf("Key %d not found.\n", key);
            }
        }
        else if (input_menu == 't') {
            break;
        }
        else {
            printf("Invalid command.\n");
        }
    }
    return 0;
}
