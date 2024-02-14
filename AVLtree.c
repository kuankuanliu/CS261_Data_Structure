#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef LT
#define LT(A, B) ((A) < (B))
#endif

struct AVLnode {
    int value;
    struct AVLnode *left;
    struct AVLnode *right;
    int height;
};
struct AVLTree {
    struct AVLnode * root;
    int size;
};
void initAVLTree(struct AVLTree * tree) {
    tree->size = 0; tree->root = 0;
}
struct AVLTree * createAVLTree() {
    struct AVLTree * newTree = malloc(sizeof(struct AVLTree));
    initAVLTree(newTree);
    return newTree;
}
int sizeAVLTree(struct AVLTree * tree) {
    assert(tree != 0);
    return tree->size;
}
void _destroyAVLTree(struct AVLnode * current) {
    if (current != 0) {
        _destroyAVLTree(current->left);
        _destroyAVLTree(current->right);
        free(current);
    }
}
void destroyAVLTree(struct AVLTree * tree) {
    _destroyAVLTree(tree->root);
    free(tree);
    tree = 0;
}
//rotate//
struct AVLnode * rotateLeft(struct AVLnode * current) {
    struct AVLnode * a = current->right;
    struct AVLnode * b = a->left;
    a->left = current;
    current->right = b;
    return a;
}
struct AVLnode * rotateRight(struct AVLnode * current) {
    struct AVLnode * a = current->left;
    struct AVLnode * b = a->right;
    a->right = current;
    current->left = b;
    return a;
}

int h(struct AVLnode * current)
{
    if (current == 0) {
        return -1;
    }

    return current->height;
}
int bf(struct AVLnode * current)
{
    return h(current->right) - h(current->left);
}
void setHeight(struct AVLnode * current) {
    int lch = h(current->left);
    int rch = h(current->right);
    if (lch < rch) current->height = 1 + rch;
    else current->height = 1 + lch;
}
struct AVLnode * balance(struct AVLnode * current) {

    int cbf = bf(current);

    if (cbf < -1) {
        if (bf(current->left) > 0)
            current->left = rotateLeft(current->left);
        return rotateRight(current);
    }

    else if (cbf > 1) {
        if (bf(current->right) < 0)
            current->right = rotateRight(current->right);
        return rotateLeft(current);
    }

    setHeight(current);
    return current;
}

struct AVLnode * AVLnodeAdd(struct AVLnode* current, int newValue) {
    struct AVLnode * newnode;
    if (current == 0) {
        newnode = (struct AVLnode *) malloc(sizeof(struct AVLnode));
        assert(newnode != 0);
        newnode->value = newValue;
        newnode->left = newnode->right = 0;
        newnode->height = 0;
        return newnode;
    }
    else if (LT(newValue, current->value))
        current->left = AVLnodeAdd(current->left, newValue);
    else current->right = AVLnodeAdd(current->right, newValue);
    return balance(current);
}
//addnode//
void addAVLTree(struct AVLTree * tree, int newValue) {

    assert(tree != 0);

    tree->root = AVLnodeAdd(tree->root, newValue);
    tree->size++;
}

int containsAVLnode(struct AVLnode * current, int d) {
    if (current == 0) {
        return 0;
    }
    else if (current->value == d) {
        return 1;
    }
    else if (LT(d, current->value)) {
        return containsAVLnode(current->left, d);
    }

    else {
        return containsAVLnode(current->right, d);
    }
}
int containsAVLTree(struct AVLTree * tree, int d) {

    assert(tree != 0);

    return containsAVLnode(tree->root, d);

}

int _leftMost(struct AVLnode * cur) {
    while (cur->left != 0) {
        cur = cur->left;
    }
    return cur->value;
}
struct AVLnode * _removeLeftmost(struct AVLnode *cur) {
    struct AVLnode *temp;
    if (cur->left != 0)
    {
        cur->left = _removeLeftmost(cur->left);
        return balance(cur);
    }
    temp = cur->right;
    free(cur);
    return temp;
}
struct AVLnode * _removeNode(struct AVLnode *cur, int val) {
    if (val == cur->value) {
        if (cur->right == 0 && cur->left == 0) {
            free(cur);
            return 0;
        }
        else if (cur->right == 0) {
            struct AVLnode * tempNode = cur->left;
            free(cur);
            cur = 0;
            return tempNode;
        }
        else if (cur->left == 0) {
            struct AVLnode * tempNode = cur->right;
            free(cur);
            cur = 0;
            return tempNode;
        }
        else {
            cur->value = _leftMost(cur->right);
            cur->right = _removeLeftmost(cur->right);
        }
    }
    else if (LT(val, cur->value)) {
        cur->left = _removeNode(cur->left, val);
    }
    else {
        cur->right = _removeNode(cur->right, val);

    }
    return balance(cur);
}
//removeNode//
void removeAVLTree(struct AVLTree *tree, int val) {
    if (containsAVLTree(tree, val)) {
        tree->root = _removeNode(tree->root, val);
        tree->size--;
    }
}

void printInorder(struct AVLnode* node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    printf("%d ", node->value);
    printInorder(node->right);
}
void printPreorder(struct AVLnode* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->value);
    printPreorder(node->left);
    printPreorder(node->right);
}
void printPostorder(struct AVLnode* node)
{
    if (node == NULL)
        return;
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->value);
}

int main() {
    struct AVLTree * testAVLtree = createAVLTree();
    addAVLTree(testAVLtree, 5);
    addAVLTree(testAVLtree, 3);
    addAVLTree(testAVLtree, 6);
    addAVLTree(testAVLtree, 7);
    addAVLTree(testAVLtree, 2);
    addAVLTree(testAVLtree, 1);
    addAVLTree(testAVLtree, 10);
    addAVLTree(testAVLtree, 22);
    removeAVLTree(testAVLtree, 1);
    removeAVLTree(testAVLtree, 3);
    printf("Inorder:\n");
    printInorder(testAVLtree->root);
    printf("\n");
    printf("Preorder:\n");
    printPreorder(testAVLtree->root);
    printf("\n");
    printf("Postorder:\n");
    printPostorder(testAVLtree->root);
    printf("\n");
    destroyAVLTree(testAVLtree);
    return 0;
}
