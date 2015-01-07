/* CS261- Assignment 1 - Q.3*/
/* Name: Aryan Aziz
 * Date: 6-29-14
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
	int temp;
     for(int i = 0; i < 20; i++) {
     	for(int j = i; j < 20; j++) {
     		if(number[i] > number[j]) {
     			temp = number[i];
     			number[i] = number[j];
     			number[j] = temp;
     		}
     	}
     }     
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int * array = malloc(n * sizeof(int));
    
    /*Fill this array with random numbers, using rand().*/
    for(int i = 0; i < 20; i++) {
    	array[i] = rand();
    }
    
    /*Print the contents of the array.*/
    for(int i = 0; i < 20; i++) {
    	printf("%d\n", array[i]);
    }

    /*Pass this array along with n to the sort() function of part a.*/
    sort(array, n);
    
    /*Print the contents of the array.*/    
    printf("\n\n\n");
    for(int i = 0; i < 20; i++) {
    	printf("%d\n", array[i]);
    }

    return 0;
}
