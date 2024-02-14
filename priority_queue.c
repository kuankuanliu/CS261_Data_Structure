

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
struct dynarray
{
  void** data;
  int size;
  int capacity;
};


#define DYNARRAY_INIT_CAPACITY 8

/*
 * This function allocates and initializes a new, empty dynamic array and
 * returns a pointer to it.
 */
struct dynarray* dynarray_create() {
  struct dynarray* da = malloc(sizeof(struct dynarray));
  assert(da);

  da->data = malloc(DYNARRAY_INIT_CAPACITY * sizeof(void*));
  assert(da->data);
  da->size = 0;
  da->capacity = DYNARRAY_INIT_CAPACITY;

  return da;
}

/*
 * This function frees the memory associated with a dynamic array.  Freeing
 * any memory associated with values stored in the array is the responsibility
 * of the caller.
 *
 * Params:
 *   da - the dynamic array to be destroyed.  May not be NULL.
 */
void dynarray_free(struct dynarray* da) {
  assert(da);
  free(da->data);
  free(da);
}

/*
 * This function returns the size of a given dynamic array (i.e. the number of
 * elements stored in it, not the capacity).
 */
int dynarray_size(struct dynarray* da) {
  assert(da);
  return da->size;
}


/*
 * Auxilliary function to perform a resize on a dynamic array's underlying
 * storage array.
 */
void _dynarray_resize(struct dynarray* da, int new_capacity) {
  assert(new_capacity > da->size);

  /*
   * Allocate space for the new array.
   */
  void** new_data = malloc(new_capacity * sizeof(void*));
  assert(new_data);

  /*
   * Copy data from the old array to the new one.
   */
  for (int i = 0; i < da->size; i++) {
    new_data[i] = da->data[i];
  }

  /*
   * Put the new array into the dynarray struct.
   */
  free(da->data);
  da->data = new_data;
  da->capacity = new_capacity;
}

/*
 * This function inserts a new value to a given dynamic array.  The new element
 * is always inserted at the *end* of the array.
 *
 * Params:
 *   da - the dynamic array into which to insert an element.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_insert(struct dynarray* da, void* val) {
  assert(da);
  /*
   * Make sure we have enough space for the new element.  Resize if needed.
   */

  if (da->size == da->capacity) {
    _dynarray_resize(da, 2 * da->capacity);
  }

  

  /*
   * Put the new element at the end of the array.
   */
  da->data[da->size] = val;
  da->size++;
}

/*
 * This function removes an element at a specified index from a dynamic array.
 * All existing elements following the specified index are moved forward to
 * fill in the gap left by the removed element.
 *
 * Params:
 *   da - the dynamic array from which to remove an element.  May not be NULL.
 *   idx - the index of the element to be removed.  The value of `idx` must be
 *     between 0 (inclusive) and n (exclusive), where n is the number of
 *     elements stored in the array.
 */
void dynarray_remove(struct dynarray* da, int idx) {
  assert(da);
  assert(idx < da->size && idx >= 0);

  /*
   * Move all elements behind the one being removed forward one index,
   * overwriting the element to be removed in the process.
   */
  for (int i = idx; i < da->size - 1; i++) {
    da->data[i] = da->data[i+1];
  }

  da->size--;
}

/*
 * This function returns the value of an existing element in a dynamic array.
 *
 * Params:
 *   da - the dynamic array from which to get a value.  May not be NULL.
 *   idx - the index of the element whose value should be returned.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 */
void* dynarray_get(struct dynarray* da, int idx)
{
  assert(da);
  //assert(idx < da->size && idx >= 0);

  return da->data[idx];
}

/*
 * This function updates (i.e. overwrites) the value of an existing element in
 * a dynamic array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   val - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_set(struct dynarray* da, int idx, void* val) {
  assert(da);
  assert(idx < da->size && idx >= 0);

  da->data[idx] = val;
}


struct pq
{
    
  struct dynarray* dyn_array;

};


/*
* Struct to store the elements of the priority queue
*/

typedef struct node
{

    void* value;
    int priority;

}node;



typedef struct pq pq;
/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */

pq* createPq()
{
    
    // FIXME
    struct pq* new_queue = malloc(sizeof(struct pq));
    new_queue->dyn_array = dynarray_create();
    return new_queue;

}


/*
 * This function should free the memory allocated to a given priority queue
 */

void freePq(pq* myPq)
{
    dynarray_free(myPq->dyn_array);
    free(myPq);
  // FIXME
 
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 */

int isemptyPq(pq* myPq)
{
    return !dynarray_size(myPq->dyn_array);
    // FIXME
    
}


/*
 * This function should add a given element into a priority queue with a
 * specified priority value.
 */
void percolate_up(struct pq* pq, int index) {
    while (index > 0) {
        int parent_node = (index - 1) / 2;
        
        node* idx = dynarray_get(pq->dyn_array, index);
        node* parent = dynarray_get(pq->dyn_array, parent_node);
        
        if (idx->priority >= parent->priority) break;

        dynarray_set(pq->dyn_array, index, parent);
        dynarray_set(pq->dyn_array, parent_node, idx);
        index = parent_node;
    }
}

void addPq(pq* myPq, void* value, int priority)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->value = value;
      new_node->priority = priority;
    dynarray_insert(myPq->dyn_array, new_node);
    percolate_up(myPq, dynarray_size(myPq->dyn_array) - 1);
  // FIXME
  
}


/*
 * This function should return the value of the item with lowest priority
 *
 */

void* getPq(pq* myPq)
{
    node* pq_data = dynarray_get(myPq->dyn_array, 0);
    return pq_data->value;
  //FIXME

}


/*
 * This function should remove the value with lowest priority
 */
int pq_first_priority(struct pq* pq) {
    node* pq_priority = dynarray_get(pq->dyn_array, 0);
    return pq_priority->priority;
}

void percolate_down(struct pq* pq, int index) {
    int left_node = (2 * index) + 1;
    int right_node = (2 * index) + 2;
    
    node* left_priority;
    node* right_priority;
   node* index_priority;

    if (left_node >= dynarray_size(pq->dyn_array)) {
        left_priority = NULL;
    } else {
        left_priority = dynarray_get(pq->dyn_array, left_node);
    }
    
    if (right_node >= dynarray_size(pq->dyn_array)) {
        right_priority = NULL;
    } else {
        right_priority = dynarray_get(pq->dyn_array, right_node);
    }

    if (index >= dynarray_size(pq->dyn_array)) {
        return;
    } else {
        index_priority = dynarray_get(pq->dyn_array, index);
    }

    if (left_priority == NULL && right_priority == NULL) return;
    
    if (left_priority != NULL && right_priority == NULL) {
        if (index_priority->priority > left_priority->priority) {
            dynarray_set(pq->dyn_array, index, left_priority);
            dynarray_set(pq->dyn_array, left_node, index_priority);
            percolate_down(pq, left_node);
        } else return;
    } else if (left_priority == NULL && right_priority != NULL) {
        if (index_priority->priority > right_priority->priority) {
            dynarray_set(pq->dyn_array, index, right_priority);
            dynarray_set(pq->dyn_array, right_node, index_priority);
            index = right_node;
            percolate_down(pq, right_node);
        } else return;
    } else if (left_priority != NULL && right_priority != NULL) {
        if (left_priority->priority < right_priority->priority) {
            dynarray_set(pq->dyn_array, index, left_priority);
            dynarray_set(pq->dyn_array, left_node, index_priority);
            percolate_down(pq, left_node);
        } else {
            dynarray_set(pq->dyn_array, index, right_priority);
            dynarray_set(pq->dyn_array, right_node, index_priority);
            percolate_down(pq, right_node);
        }
    }
}
void removePq(struct pq* myPq)
{
  // FIXME
    dynarray_set(myPq->dyn_array, 0, dynarray_get(myPq->dyn_array, dynarray_size(myPq->dyn_array) - 1));
    dynarray_remove(myPq->dyn_array, dynarray_size(myPq->dyn_array) - 1);
    percolate_down(myPq, 0);
}


/*
 * This function should print the values that are in the pq
 * and their priorities on the screen
 * from the queue.
 */

void printPq(struct pq* myPq)
{
  // FIXME
}
#define TASK_DESC_SIZE 128
struct task {
    char description[TASK_DESC_SIZE];      /* description of the task */
    int priority;                          /* task priority */
};

typedef  struct task* taskpq;
taskpq createTask (int priority, char *desc)
{
    /*FIXME: Write this */
    taskpq newTask = (struct task *)malloc(sizeof(struct task));
    
    strcpy(newTask->description, desc);
    newTask->priority = priority;
    
    return newTask;
}


void loadpq(pq*pq, FILE *filePtr)
{
    taskpq task;
    char line[100];  /* Assume lines < 100 */
    char desc[TASK_DESC_SIZE];
    int priority;

    /* Read the priority first, then the description.
     * fgets() is used to read string with spaces
     */

    while(fgets(line, sizeof(line), filePtr) != 0)
    {
      sscanf(line, "%d\t%[^\n]", &priority, desc);
      task = createTask(priority, desc);
    addPq(pq, task->description, task->priority);
    } /* should use feof to make sure it found eof and not error*/
}

void savepq(pq*pq, FILE *filePtr)
{
    int i;
    node* task;
    assert(dynarray_size(pq->dyn_array) > 0);
    for(i = 0; i < dynarray_size(pq->dyn_array); i++)
    {
      task = dynarray_get(pq->dyn_array, i);
      fprintf(filePtr, "%d\t%s\n", task->priority, (char*)(task->value));
    }
}



void printList(pq*pq)
{
    int i;
    char *description = malloc(sizeof(char)*250);
    struct pq* copylist;
    copylist = createPq();
    for(i = 0; i < pq->dyn_array->size; i++){
        copylist->dyn_array->data[i] = pq->dyn_array->data[i];
        
        copylist->dyn_array->size = pq->dyn_array->size;
    }
    description = ((struct task *)getPq(copylist))->description;
    taskpq task;
    while(dynarray_size(copylist->dyn_array) > 0)
        {
            task = getPq(copylist);
            // task = getDynArr(temp,0);

            /* print the task */
            printf("%d:  %s\n\n", task->priority, task->description);
            /* remove the task , but let's not free up the memory it's pointing to since old Arr is using it!*/
            /* BINHEAP FIXME */
            removePq(copylist);
            // removeAtDynArr(temp, 0);
        }
    printf("'%s'\n", description);
}

int main(int argc, char** argv)
{
  // FIXME
     char *filename = malloc(sizeof(char)*250);
     char *description = malloc(sizeof(char)*250);
     int priority;
     char cmd = ' ';
     struct pq* mainList;
     mainList = createPq();

     printf("\n\n TO-DO LIST APPLICATION \n\n");
     
     do
     {
         printf("Press:\n"
                "'l' to load to-do list from a file\n"
                "'s' to save to-do list to a file\n"
                "'a' to add a new task\n"
                "'g' to get the first task\n"
                "'r' to remove the first task\n"
                "'p' to print the list\n"
                "'e' to exit the program\n"
                );
         /* get input command (from the keyboard) */
         cmd = getchar();
         /* clear the trailing newline character */
         while (getchar() != '\n');
         
         switch (cmd)
         {
             case 'l':
                 printf("Please enter the filenmae: ");
                 fgets(filename, 100, stdin);
                 if(filename[strlen(filename) - 1] == '\n')
                     filename[strlen(filename) - 1] = 0;
                 FILE *reader = fopen(filename, "r");
                 loadpq(mainList, reader);
                 printf("The list has been loaded from file successfully.\n");
                 fclose(reader);
                 break;
                 
             case 's':
                 printf("Please enter the filename: ");
                 fgets(filename, 100, stdin);
                 if(filename[strlen(filename) - 1] == '\n')
                     filename[strlen(filename) - 1] = 0;
                 FILE *writer = fopen(filename, "w+");
                 savepq(mainList, writer);
                 printf("The list has been saved io the file successfully. \n");
                 fclose(writer);
                 break;
                 
             case 'a':
                 printf("Please enter the task description: ");
                 fgets(description, 100, stdin);
                 if (description[strlen(description) - 1] == '\n')
                     description[strlen(description) - 1] = 0;
                 printf("Please enter the task priority (0-999): ");
                 scanf("%d", &priority);
                 while (getchar() != '\n');
                 taskpq dummy = createTask(priority, description);
                 addPq(mainList, dummy->description, dummy->priority);
                 printf("The task '%s' has been added to the list.\n", description);
                 break;
                 
             case 'g':
                 if (!isemptyPq(mainList))
                     printf("The first task is: %s\n", ((struct task *)getPq(mainList))->description);
                 else
                     printf("The list is empty...\n");
                 break;
                 
             case 'r':
                 if (isemptyPq(mainList))
                     printf("The list is empty...\n");
                 else
                 {
                     description = ((struct task *)getPq(mainList))->description;
                     removePq(mainList);
                     printf("The first task '%s' has been removed from the list.\n", description);
                 }
                 break;
                 
             case 'p':
                 if(isemptyPq(mainList))
                     printf("The list is empty...\n");
                 else
                     printList(mainList);
                 break;
                 
             case 'e':
                 printf("Exiting Application...\n");
                 break;
         }
         
     }
     while(cmd != 'e');

    freePq(mainList);
     
    return 0;

}

