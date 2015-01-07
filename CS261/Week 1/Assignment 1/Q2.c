/* CS261- Assignment 1 - Q.2*/
/* Name: Aryan Aziz
 * Date: 6-29-14
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    
    /*Set b to half its original value*/
    *b = *b / 2;

    /*Assign a+b to c*/
    c = *a + *b;

    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    /*Print the values of x, y and z*/
    printf("%d\n", x);
    printf("%d\n", y);
    printf("%d\n", z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    //foo(&x, &y, z); //Commented out because I didn't want to run foo twice. Foo is being called on line 38. 
    
    /*Print the value returned by foo*/
    printf("%d\n", foo(&x, &y, z));
    
    /*Print the values of x, y and z again*/
    printf("%d\n", x);
    printf("%d\n", y);
    printf("%d\n", z);
 
    /*Is the return value different than the value of z?  Why?*/
    //Yes because we are not changing the original variable/memory slot, just a "copy" of the variable. 
    return 0;
}
    
    
