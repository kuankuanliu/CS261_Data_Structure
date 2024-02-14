#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bst.h"
#include "structs.h"

struct Node
{
    TYPE         value;
    struct Node* left;
    struct Node* right;
};

struct BSTree
{
    struct Node* root;
    int          count;
};


/*----------------------------------------------------------------------------*/
//BINARY SEARCH TREE FUNCTIONS GO HERE
/*----------------------------------------------------------------------------*/

struct BSTree* newBSTree()                        // Allocates and initializes the BST
{
    /*write this*/
    BSTree* newTree=(BSTree*) malloc(sizeof(BSTree));
    assert(newTree != NULL);
    newTree->count = 0;
    newTree->root = NULL;
    return newTree;
}

void _freeBST(struct Node *node)
{
    if (node != NULL) {
        _freeBST(node->left);
        _freeBST(node->right);
        free(node);
    }
}

void deleteBSTree(BSTree* myTree)                // Deallocate nodes in BST and deallocate the BST structure
{
    /*write this*/
    assert(myTree != NULL);
    if (myTree->root == NULL){
        free(myTree);
        return;
    }
    else if ( myTree->root != NULL) {
    _freeBST(myTree->root);
    myTree->root = 0;
    }
    myTree->count  = 0;
    free(myTree);
    
}
int isEmptyBSTree(BSTree* myTree)                // Returns "1" if the BST is empty or "0" if not
{
    /*write this*/
    assert(myTree != NULL);
    if (myTree->count == 0) {
        return 1;
    }
    return 0;
    
}
int sizeBBSTree(BSTree* myTree)                // Returns the size of the BST
{
    /*write this*/
    return myTree->count;
}

struct Node *_addNode(struct Node *current, TYPE value)
{
    /*write this*/
    assert(value != NULL);
    if (current == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        assert(newNode != NULL);
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    else {
        int comparisonResult = compare(value, current->value);
        if (comparisonResult == -1){
            current->left = _addNode(current->left, value);
        }
        else if (comparisonResult >= 0) {
            current->right = _addNode(current->right, value);
        }
    }
    
    return current;
}
void addBSTree(BSTree* myTree, TYPE value)        // Adds an element into the BST
{
    /*write this*/
    myTree->root = _addNode(myTree->root, value);
    myTree->count++;
}
int containsBSTree(BSTree* myTree, TYPE value)    // Returns "1" if the BST contains the specified element or "0" if not
{
    /*write this*/
    assert(myTree != NULL);
    assert(value != NULL);
    struct Node* current = myTree->root;
    while (compare(value, current->value) != 0) {
        if (compare(value, current->value) == -1) {
            current = current->left;
        }
        else if (compare(value, current->value) == 1) {
            current = current->right;
        }
        if (current == NULL) {
            return 0;
        }
    }
    return 1;
    
}
TYPE minBSTree(BSTree* myTree)                    // Returns the minimum value in the BST
{
    /*write this*/
    struct Node* current = myTree->root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->value;
}
TYPE maxBSTree(BSTree* myTree)                    // Returns the maximum value in the BST
{
    /*write this*/
    struct Node* current = myTree->root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->value;
}

TYPE _leftMost(struct Node *current)
{
    /*write this*/
    assert(current != NULL);
    while (current->left != NULL) {
        current = current->left;
    }
    return current->value;
}
struct Node *_removeLeftMost(struct Node *current)
{
    /*write this*/
    assert(current != NULL);
    if (current->left != NULL) {
        current->left = _removeLeftMost(current->left);
        return current;
    }
    else {
        struct Node* tempNode = current->right;
        free(current);
        return tempNode;
    }
}
struct Node *_removeNode(struct Node *current, TYPE value)
{
    /*write this*/
    
    assert(current != NULL);
    assert(value != NULL);
    int compareResults = compare(value, current->value);
    if (compareResults == -1) {
        current->left = _removeNode(current->left, value);
    }
    else if (compareResults == 1) {
        current->right = _removeNode(current->right, value);
    }
    else if (compareResults == 0) {
        if (current->right == NULL) {
            struct Node* tempNode = current->left;
            free(current);
            return tempNode;
        }
        else {
            
            current->value = _leftMost(current->right);
            current->right = _removeLeftMost(current->right);
        }
    }
    return current;

}
void removeBSTree(BSTree *tree, TYPE value)    // Remove the specific element from the BST
{
    /*write this*/
    if (containsBSTree(tree, value)) {
        tree->root = _removeNode(tree->root, value);
        tree->count--;
    }
}
void printNode(struct Node *cur) {
    {
        if(cur==NULL)
            return;

        printNode(cur->left);
        print_type(cur->value);
        printf(" ");
        printNode(cur->right);
    }
}
void printBSTree(BSTree* myTree)                // Prints the values in the BST.
{
    /*write this*/
    printf("Inorder: ");
    if (myTree == 0) return;
    printNode(myTree->root);
    printf("\n");
}




/*----------------------------------------------------------------------------*/

// Test value stuff -----

struct TestValues
{
    struct data* values;
    int n;
};

void initValue(struct data* value, int number, const char* name)
{
    value->number = number;
    value->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(value->name, name);
}

void freeValue(struct data* value)
{
    free(value->name);
}

struct TestValues* createValues()
{
    struct TestValues* values = malloc(sizeof(struct TestValues));
    values->n = 4;
    values->values = malloc(values->n * sizeof(struct data));
    
    initValue(&(values->values[0]), 50, "rooty");
    initValue(&(values->values[1]), 13, "lefty");
    initValue(&(values->values[2]), 110, "righty");
    initValue(&(values->values[3]), 10, "lefty of lefty");
    
    return values;
}

void destroyValues(struct TestValues* values)
{
    for (int i = 0; i < values->n; ++i)
    {
        freeValue(&(values->values[i]));
    }
    free(values->values);
    free(values);
}

// -----

void printTestResult(int predicate, char *nameTestFunction, char 
*message){
    if (predicate)
        printf("%s(): PASS %s\n",nameTestFunction, message);
    else
        printf("%s(): FAIL %s\n",nameTestFunction, message);        
}

/**
 * Tests adding 4 nodes to the BST.
 */
void testAddNode()
{
    struct TestValues* tv = createValues();
    struct BSTree *tree	= newBSTree();
    
    // Add all values to the tree
    for (int i = 0; i < tv->n; ++i)
    {
        addBSTree(tree, &(tv->values[i]));
        if (tree->count != i + 1)
        {
            printf("addNode() test: FAIL to increase count when inserting\n");
            return;
        }
    }
    
    // Check that root node is rooty
    if (tree->root->value != &(tv->values[0]))
    {
        printf("addNode() test: FAIL to insert 50 as root\n");
        return;
    }
    else
    {
        printf("addNode() test: PASS when adding 50 as root\n");
    }
    
    if (tree->root->left->value != &(tv->values[1]))
    {
        printf("addNode() test: FAIL to insert 13 as left child of root\n");
        return;
    }
    else
    {
        printf("addNode() test: PASS when adding 13 as left of root\n");
    }
    
    if (tree->root->right->value != &(tv->values[2]))
    {
        printf("addNode() test: FAIL to insert 110 as right child of root\n");
        return;
    }
    else
    {
        printf("addNode() test: PASS when adding 110 as right of root\n");
    }
    
    if (tree->root->left->left->value != &(tv->values[3]))
    {
        printf("addNode() test: FAIL to insert 10 as left child of left of root\n");
        return;
    }
    else
    {
        printf("addNode() test: PASS when adding 10 as left of left of root\n");
    }
    
    deleteBSTree(tree);
    destroyValues(tv);
}

/**
 * Tests that the BST contains the added elements,
 * and that it does not contain an element that was not added.
 */
void testContainsBSTree()
{
    struct TestValues* tv = createValues();
    struct BSTree *tree	= newBSTree();
    
    // Create value not added to the tree
    struct data notInTree;
    notInTree.number = 111;
    notInTree.name = "not in tree";
    
    // Add all other values to the tree
    for (int i = 0; i < tv->n; ++i)
    {
        addBSTree(tree, &(tv->values[i]));
    }
    
    printTestResult(containsBSTree(tree, &(tv->values[0])), "containsBSTree", "when test containing 50 as root");
    printTestResult(containsBSTree(tree, &(tv->values[1])), "containsBSTree", "when test containing 13 as left of root");
    printTestResult(containsBSTree(tree, &(tv->values[2])), "containsBSTree", "when test containing 110 as right of root");
    printTestResult(containsBSTree(tree, &(tv->values[3])), "containsBSTree", "when test containing 10 as left of left of root");
    
    printTestResult(!containsBSTree(tree, &notInTree), "containsBSTree", "when test containing 111, which is not in the tree");
    
    deleteBSTree(tree);
    destroyValues(tv);
}

/**
 * Tests leftMost.
 */
void testMinMax()
{
	struct TestValues* tv = createValues();
    BSTree* tree	= newBSTree();

    for (int i = 0; i < tv->n; ++i)
    {
        addBSTree(tree, &(tv->values[i]));
    }
	
	if(compare(minBSTree(tree), &(tv->values[3])) == 0)
		printf("Test minBSTree(): PASS\n");
    else
        printf("Test minBSTree(): FAIL\n");
	
	if(compare(maxBSTree(tree), &(tv->values[2])) == 0)
		printf("Test maxBSTree(): PASS\n");
    else
        printf("Test maxBSTree(): FAIL\n");
	
	deleteBSTree(tree);
    destroyValues(tv);
}



/**
 * Tests removal of all nodes.
 */
void testRemoveBSTree()
{
    struct TestValues* tv = createValues();
    BSTree *tree	= newBSTree();

    for (int i = 0; i < tv->n; ++i)
    {
        addBSTree(tree, &(tv->values[i]));
    }
    
	printf("Original tree:\n");
	printBSTree(tree);
	
    removeBSTree(tree, &tv->values[3]);
	printf("The tree below should not contain the value 10\n");
	printBSTree(tree);
	        
    removeBSTree(tree, &tv->values[2]);
	printf("The tree below should not contain the value 110\n");
	printBSTree(tree);
	   
    removeBSTree(tree, &tv->values[1]);
	printf("The tree below should not contain the value 13\n");
	printBSTree(tree);
        
    removeBSTree(tree, &tv->values[0]);
	printf("The tree below should be empty\n");
	printBSTree(tree);
    
    deleteBSTree(tree);
    destroyValues(tv);
}


// Main function for testing

int main(int argc, char *argv[])
{	

   /* After implementing your code, you must uncomment the following calls to the test functions and test your code. Otherwise, you will not receive any 
points */

  	testAddNode();
	
	printf("\n");
  	testContainsBSTree();
	
	printf("\n");
    testMinMax();
	
	printf("\n");
    testRemoveBSTree();
    
	return 0;
}
