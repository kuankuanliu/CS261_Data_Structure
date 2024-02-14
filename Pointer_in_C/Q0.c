/* CS261- Assignment 1A - Question 3
   Name: Kuan-Ting Liu, Parthiveshwar Sharma Pagidimarri
   Date: 2022/10/01
   Solution description:
    question 3: Follow the coding, becasue the function fooA() will add 5 on the value of the address pointing to. Therefore, the value of x will be change. so yes the x will be different after fooA().
    question 5: The function fooB() will minus 1 on the value of the address pointing to. Therefore, the value of x will be change. so yes the x will be different after foob().
  
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr)
{
    // Print the value and address of the integer pointed to by iptr
    printf("iptr value = %d\n", *iptr);
    printf("iptr address = %p\n", iptr);
     // Increment the value of the integer pointed to by iptr by 5
    *iptr += 5;
     // Print the address of iptr itself
    printf("iptr address = %p\n", iptr);
}

void fooB(int* jptr)
{
    // Print the value and address of the integer pointed to by jptr
    printf("jptr value = %d\n", *jptr);
    printf("jptr address = %p\n", jptr);
     // Decrement jptr by 1
    *jptr -= 1;
     // Print the address of jptr itself
    printf("jptr address = %p\n", jptr);
}


int main()
{
    // Declare an integer x and initialize it randomly to a value in [0,10]
    srand((unsigned int)time(0));
    int x =rand() % 11;
    // Print the value and address of x
    printf("x = %d\n", x);
    printf("x address = %p\n", &x);
    // Call fooA() with the address of x
    fooA(&x);
    // Print the value of x
    printf("x = %d\n", x);
    // Call fooB() with the address of x
    fooB(&x);
    // Print the value and address of x
    printf("x = %d\n", x);
    printf("x address = %p\n", &x);
    return 0;
}


