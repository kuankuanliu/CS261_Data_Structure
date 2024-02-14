/* CS261- Assignment 1A - Question 3
   Name: Kuan-Ting Liu, Parthiveshwar Sharma Pagidimarri
   Date: 2022/10/01
   Solution description:
    Follow the coding description, we generate a funciotn foo() to swap the pointer
    varibles a and b: first we declare a temperaory varible tp to store a. and then we can
    store the varible b to a, and then tp to the b.
    question 4: the return value and z is different. because z is just a pass by value into the foo(). When doing function, z will copy on value to work on the foo(), after the foo() finished, the result value is the foo() returned.
    x and y should not be changed because the function foo() using *a and *b as the variables. That means the varible of *a and *b are only 2 copy from the address value x and y. So like z, they only work in the foo().
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int *a, int *b, int c)
{
    // Swap the addresses stored in the pointer variables a and b
    int *tp;
    tp = a;
    a = b;
    b = tp;
    // Decrement the value of integer variable c
    c = c - 1;
    // Return c
    return c;
}

int main()
{
    // Declare three integers x,y and z and initialize them randomly to values in [0,10]
    srand((unsigned int)time(0));
    int x =rand() % 11;
    int y =rand() % 11;
    int z =rand() % 11;
    // Print the values of x, y and z
    printf("x = %d, y = %d, z =%d\n", x,y,z);
    // Call foo() appropriately, passing x,y,z as parameters
    int result = foo(&x, &y, z);
    // Print the values of x, y and z
    printf("x = %d, y = %d, z =%d\n", x,y,z);
    // Print the value returned by foo
    printf("result of foo()= %d\n)", result);
    
    return 0;
}
    
