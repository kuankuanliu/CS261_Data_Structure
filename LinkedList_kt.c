/***********************************************************
* Author: Kason Castillo, Kuan-Ting Liu
* Email: castilka@oregonstate.edu ;  liukuan@oregonstate.edu
* Date Created: 10/20/22
* Filename: linkedList.c
*
* Overview:
*	This program is a linked list implementation of the deque and bag ADTs. 
*	Note that both implementations utilize a linked list with
*	both a front and back sentinel and double links (links with
*	next and prev pointers).
************************************************************/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"

#ifndef FORMAT_SPECIFIER
#define FORMAT_SPECIFIER "%d"
#endif


/* ************************************************************************
	Structs Link and LinkedList
************************************************************************ */
struct Link {
	TYPE data;
	Link* next;
	Link* previous;
};

struct LinkedList {
	int size;
	Link* head;
	Link* tail;
};

/* ************************************************************************
	Linked List Functions
************************************************************************ */


LinkedList* linkedListCreate() {
	LinkedList* newList = (LinkedList*) malloc(sizeof(LinkedList));
	assert(newList != NULL);
	newList->size = 0;
	newList->head = NULL;
	newList->tail = NULL;
	return newList;
}


void deletelinkedList(LinkedList* list) {
	assert(list != NULL);
	if (list->head == NULL) {
		free(list);
		return;
	}
	
	Link* tmp;
	
	while (list->head->next != NULL) {
		tmp = list->head->next;
		free(list->head);
		list->head = tmp;
	}
	
	free(list->head);
	free(list);
}


int sizelinkedList(LinkedList* myList) {
	assert(myList != NULL);
	return myList->size;
}


int isEmptyLinkedList(LinkedList* myList) {
	assert(myList != NULL);
	if (myList->size == 0) {
		return 1;
	}
	return 0;
}


void addLinkBefore(LinkedList* list, TYPE value) {
	assert (list != NULL);
	Link* newLink = (Link*) malloc(sizeof(Link));
	newLink->data = value;
	newLink->previous = NULL;
	
	Link* tmp = list->head;
	
	if (tmp == NULL) {
		list->head = newLink;
		list->tail = newLink;
		list->size++;
		newLink->next = NULL;
		return;
	}
	
	tmp->previous = newLink;
	newLink->next = tmp;
	list->head = newLink;
	list->size++;
}


void removeLink(LinkedList* list, TYPE value) {
    assert(list != NULL);
    Link* iterator = NULL;
    iterator = list->head;

    /* If the list is not empty*/
    if (list->head != NULL && list->tail != NULL) {
        /* Check if there is only one element in the list */
        if (list->head == list->tail) {
            list->head = NULL;
            list->tail = NULL;
            free(iterator);
        } else {
            /* Removing the first element (Remove from beginning) */
            if (list->head->data == value)
            {
                Link* nodeToRemove = iterator;
                list->head = nodeToRemove->next;
                nodeToRemove->previous = NULL;

                free(nodeToRemove);
            } else if (list->tail->data == value) {
                /* Removing the last element (Remove from the end) */
                Link* nodeToRemove = list->tail;
                list->tail = nodeToRemove->previous;
                list->tail->next = NULL;

                free(nodeToRemove);
            } else {
                /* Loop until we find the link with the value we want to remove (Remove in between) */
                while (iterator) {
                    if (iterator->data == value) {
                        Link* nodeToRemove = iterator;
                        nodeToRemove->previous->next = nodeToRemove->next;
                        nodeToRemove->next->previous = nodeToRemove->previous;
                        free(nodeToRemove);
                    }
                    iterator = iterator->next;
                }
            }
        }
        list->size--;
    } else {
        printf("The link is empty.\n");
    }
}


void printLinkedList(LinkedList* list) {
	assert(list != NULL);
	
	if (list->size == 0) {
		printf("List is empty.\n");
		return;
	}
	
	Link* tmp = list->head;
	
	for (int i = 0; i < list->size; i++) {
		printf("%d\n", tmp->data);
		
		if (tmp->next != NULL) {
		tmp = tmp->next;
		}
	}
}


/* ************************************************************************
	Deque Functions
************************************************************************ */


Deque* dequeCreate() {
	return linkedListCreate();
}


void deleteDeque(Deque* myDeque) {
	deletelinkedList(myDeque);
}


int sizeDeque(Deque* myDeque) {
	return sizelinkedList(myDeque);
}


int isEmptyDeque(Deque* myDeque) {
	return isEmptyLinkedList(myDeque);
}


void addFrontDeque(Deque* myDeque, TYPE value) {
	addLinkBefore(myDeque,value);
}


void addBackDeque(Deque* myDeque, TYPE value) {
	if (myDeque->size == 0) {
		addLinkBefore(myDeque,value);
		return;
	}
	
	Link* tmp = (Link*) malloc(sizeof(Link));
	tmp->data = value;
	tmp->next = NULL;
	tmp->previous = myDeque->tail;
	myDeque->tail->next = tmp;
	myDeque->tail = tmp;
	myDeque->size++;
}


TYPE frontDeque(Deque* myDeque) {
	return myDeque->head->data;
}


TYPE backDeque(Deque* myDeque) {
	return myDeque->tail->data;
}


void removeFrontDeque(Deque* myDeque) {
	assert(myDeque != NULL);
	assert (myDeque->size != 0);
	removeLink(myDeque, myDeque->head->data);
}


void removeBackDeque(Deque* myDeque) {
	assert(myDeque != NULL);
	assert (myDeque->size != 0);
	Link* tmp = myDeque->tail;
	if (myDeque->size == 1) {
		myDeque->head = NULL;
		myDeque->tail = NULL;
		free(tmp);
		myDeque->size--;
		return;
	}
	
	myDeque->tail = tmp->previous;
	myDeque->tail->next = NULL;
	free(tmp);
	myDeque->size--;
}


void printDeque(Deque* myDeque) {
	printLinkedList(myDeque);
}


/* ************************************************************************
	Bag Functions
************************************************************************ */

Bag* bagCreate(){                          // Allocates and initializes the bag.
    return linkedListCreate();
}
void deleteBag(Bag* myBag){                  // Deallocates the data and deletes the bag
    deletelinkedList(myBag);
}
int sizeBag(Bag* myBag){                   // Returns the size of the bag
    return sizelinkedList(myBag);
}
int isBagEmpty(Bag* myBag){                   // Returns "1" if the bag is empty or "0" if not
    return isEmptyLinkedList(myBag);
}
void addBag(Bag* myBag, TYPE value){
    addLinkBefore(myBag, value);
}
int containsBag(Bag* myBag, TYPE value) {    // Returns "1" if the bag contains the specified element or "0" if not
    Link* iterator = NULL;
        iterator = myBag->head;

        while (iterator) {
            if (iterator->data == value)
            {
                return 1;
            }
            iterator = iterator->next;
        }
        return 0;
}
void removeBag(Bag* myBag, TYPE value){        // Removes the specific element from the bag
        removeLink(myBag, value);
}
void printBag(Bag* myBag){                  // Prints the values of the links in the bag from front to back
    printLinkedList(myBag);
}
