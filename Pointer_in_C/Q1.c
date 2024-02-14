/* CS261- Assignment 1A - Question 3
   Name: Kuan-Ting Liu, Parthiveshwar Sharma Pagidimarri
   Date: 2022/10/01
   Solution description:
    Follow the code, we give a struct student to store id and score. 1st, we declare stud = NULL for the function. And then we can use the function allocate to build up the struct student and store the id and score in the struct. For the min and max value we just a the value campare 1 by 1, the we can get the max and min value after comparison.
        And because we allocate the struct student stud, after we finished that, we free the memory.
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student
{
    int id;
    int score;
};


struct student* allocate(){
    
    // Allocate memory for ten students*/
    struct student *Students = (struct student*) malloc(sizeof(struct student)*10);
    // Return the pointer*/
    return Students;

}

void generate(struct student* students)
{
     /* Generate random and unique IDs and random scores for ten students,
        IDs being between 1 and 10, scores between 0 and 100 */
    int i, m [10];
    for (i = 1; i <= 10; i++) {
        m[i-1] =i;
    }
    for (i = 1; i <= 10; i++) {
        srand((unsigned int)time(0));
        int j = rand() % (11 - i) + i;
        int k = m[i-1];
        m[i-1] = m[j-1];
        m[j-1] = k;
    }
    for(int a = 0; a < 10; a++){
        (students + a)->id = m[a];
        (students + a)->score = rand() % 101;
    }
    
}

void output(struct student* students){
    /* Output information about the ten students in the format*/
    for(int i = 0; i < 10; i++){
        printf("ID %d Score %d\n", (students + i)->id, (students + i)->score);
    }
}

void summary(struct student* students)
{
    /* Compute and print the minimum, maximum and average scores of the
       ten students */
    int min=students[0].score;
    int max=students[0].score;
    float avg = 0;
    for(int i=0; i<10; i++){
         if(students[i].score < min){
              min = students[i].score;
         }
         if(students[i].score>max){
              max = students[i].score;
         }
         avg += students[i].score;
    }
    avg /= (float)10;

   /* Print the max, min and averages */
   printf("Maximum Score: %d\n", max);
   printf("Minimum Score: %d\n", min);
   printf("Average Score: %.2f\n", avg);
}

void deallocate(struct student* stud){

    if(stud != NULL){
        free(stud);
        stud = 0;
    }
}

int main()
{
    
    struct student* stud = NULL;
    // Call allocate
    stud = allocate(stud);
    // Call generate
    generate(stud);
    // Call output
    output(stud);
    // Call summary
    summary(stud);
    // Call deallocate
    deallocate(stud);
    
    return 0;

}
