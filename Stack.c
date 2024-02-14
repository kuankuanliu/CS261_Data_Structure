/* CS261- Assignment 2
   Name: Ryan Muriset, Kuan-Ting Liu, Cheng-Yiu Ma
   Date: 2022/10/11

*/
// DA_Stack_Bag.c: Dynamic Array, Stack and Bag implementations
#include <assert.h>
#include <stdlib.h>
#include "DA_Stack_Bag.h"


/* ************************************************************************
    Struct DynArr
************************************************************************ */

struct DynArr
{
    TYPE* values;
    int size;
    int capacity;
};

/* ************************************************************************
    Dynamic Array Functions
************************************************************************ */

// Allocates and initializes dynamic array.
DynArr* newDynArr(int capacity)
{
    struct DynArr* DynArr = malloc(sizeof(struct DynArr));
    assert(DynArr);

    DynArr->values = malloc(capacity * sizeof(int*));
    assert(DynArr->values);

    DynArr->capacity = capacity;
    DynArr->size = 0;
    return DynArr;
}

// Deallocates the data and deletes the dynamic array
void deleteDynArr(DynArr *myDA)
{
    assert(myDA);
    free(myDA->values);
    free(myDA);
}

// Returns the size of the dynamic array
int sizeDynArr(DynArr *myDA)
{
    assert(myDA);
    return myDA->size;
}

//This function will resize the array when we have reached capacity
void dynArr_resize(DynArr* myDA, int new_capacity)
{
    assert(myDA != NULL && myDA -> values != NULL);
    //Allocate new memory
    TYPE* new_values = (TYPE*) malloc(new_capacity * sizeof(TYPE));
    assert(new_values != NULL);
    
    //Copy existing data over
    for (int i = 0; i < myDA->size; i++)
    {
           new_values[i] = myDA->values[i];
      }

    //Free old values and set new values
    free(myDA->values);
    myDA->values = new_values;
    myDA->capacity = new_capacity;
}

// Adds an element to the end of the dynamic array
void addDynArr(DynArr *myDA, TYPE value)
{
    if(myDA->size == myDA->capacity)
    {
        //resize function
        dynArr_resize(myDA, 2*myDA->capacity);
    }

    myDA->values[myDA->size] = value;
    myDA->size++;
}



// Gets an element from the dynamic array from a specified position
TYPE getDynArr(DynArr *myDA, int position)
{
    assert(myDA);
    assert(position <= myDA->size && position >= 0);
    return myDA->values[position];
}

// Puts an element into the dynamic array at the specified location overwriting the element that was there.
void putDynArr(DynArr *myDA, int position, TYPE value)
{
    assert(myDA);
    assert(position <= myDA->size && position >= 0);
    myDA->values[position] = value;
}

// Swaps two specified elements in the dynamic array
void swapDynArr(DynArr *myDA, int idx_i, int  idx_j)
{
    assert(myDA);
    assert(idx_i <= myDA->size && idx_i >= 0);
    assert(idx_j <= myDA->size && idx_j >= 0);
       int temp = myDA->values[idx_i];
    myDA->values[idx_i] = myDA->values[idx_j];
    myDA->values[idx_j] = temp;
}

// Removes the element at the specified location from the array and shifts all the following elements back one spot to fill the gap
void removeAtDynArr(DynArr *myDA, int idx_i)
{
    assert(myDA);
    assert(idx_i <= myDA->size && idx_i >= 0);

    //Move all the values behind the index back one to overwrite that element
    for (int i = idx_i; i < myDA->size - 1; i++)
    {
        myDA->values[i] = myDA->values[i+1];
      }

      myDA->size--;
}

/* ************************************************************************
    Stack Interface Functions
************************************************************************ */
// Allocates and initializes the stack.
Stack *newStack(int capacity)
    {
    //    DynArr = malloc(sizeof(struct DynArr));
        assert(capacity >= 0);
        DynArr *myStack = (DynArr *)malloc(sizeof(DynArr));
        assert(myStack != 0);
        myStack->capacity = capacity;
        myStack->size = 0;
        myStack->values = (TYPE *)malloc(sizeof(TYPE) * capacity);
        assert(myStack->values != 0);
        return myStack;

    }
 // Deallocate the data and deletes the stack
void deleteStack(Stack *myStack)
{
    assert( myStack != NULL && myStack != NULL );
    free (myStack->values);
    free(myStack);
}
// Returns the size of the stack
int sizeStack(Stack *myStack)
{
    assert(myStack != NULL);
    return myStack->size;
}
// Returns "1" if the stack is empty or "0" if not
int isStackEmpty(Stack *myStack)
{
    int isEmpty = 0;
    if (sizeStack(myStack) == 0)
    
        {
            isEmpty = 1;
        }
        return isEmpty;
    
}
// Push an element onto the top of the stack
void pushStack(Stack *myStack, TYPE value)
{
    assert(myStack != 0);
    addDynArr(myStack, value);
}
// Returns the element at the top of the stack
TYPE topStack(Stack *myStack)
{
    assert(sizeStack(myStack) > 0);
    return getDynArr(myStack, sizeStack(myStack) - 1);
}
// Removes the element on top of the stack
void popStack(Stack *myStack)
{
    assert(sizeStack(myStack) > 0);
    removeAtDynArr(myStack, sizeStack(myStack) - 1);

}



/* ************************************************************************
    Bag Interface Functions
************************************************************************ */
// Allocates and initializes the bag.
Bag *newBag(int capacity)
{
    {
    //    DynArr = malloc(sizeof(struct DynArr));
        assert(capacity >= 0);
        DynArr *myBag = (DynArr *)malloc(sizeof(DynArr));
        assert(myBag != 0);
        myBag->capacity = capacity;
        myBag->size = 0;
        myBag->values = (TYPE *)malloc(sizeof(TYPE) * capacity);
        assert(myBag->values != 0);
        return myBag;
    }
}
// Deallocate the data and deletes the bag
void deleteBag(Bag *myBag)
{
    assert( myBag != NULL && myBag != NULL );
    free (myBag->values);
    free(myBag);
}
// Returns the size of the bag
int sizeBag(Bag *myBag)
{
    assert( myBag != NULL );
    return myBag->size;
}
// Returns "1" if the bag is empty or "0" if not
int isBagEmpty(Bag *myBag)
{
    int isEmpty = 0;
    if (sizeBag(myBag) == 0)
    
        {
            isEmpty = 1;
        }
        return isEmpty;
    
}
// Adds an element into the bag
void addBag(Bag *myBag, TYPE value)
{
    addDynArr(myBag, value);
}
// Returns "1" if the bag contains the specified element or "0" if not
int containsBag(Bag *myBag, TYPE value)
{
    int i = 0;
    int foundVal = 0;

    while (i < myBag->size && foundVal == 0)
    {
        if (myBag->values[i] == value) {
            foundVal = 1;
        }
        i++;
    }

    return foundVal;


}
// Remove the specific element from the bag and shifts all the following elements back one spot to fill the gap
void removeBag(Bag *myBag, TYPE value)
{
    int i;
    for (i = 0; i < myBag->size; i++) {
        if (EQ(value, myBag->values[i])) {
            removeAtDynArr(myBag, i);
            return;
        }
    }
}

