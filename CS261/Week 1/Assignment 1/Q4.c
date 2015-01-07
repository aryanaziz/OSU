/* CS261- Assignment 1 - Q.4*/
/* Name: Aryan Aziz
 * Date: 6-29-14
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

int array[10];

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
     int temp;
     for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(students[i].score < students[j].score) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
     }     
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 10;
    
    /*Allocate memory for n students using malloc.*/
    struct student* s = malloc(n * sizeof(struct student));
    
    /*Generate random IDs and scores for the n students, using rand().*/
    for(int i = 0; i < 10; i++) {
        s[i].id = i;
        s[i].score = rand() % 101;
    }
    
    /*Print the contents of the array of n students.*/
    for(int i = 0; i < 10; i++) {
        array[i] = s[i].id;
    }

    for(int i = 0; i < 10; i++) {
      printf("%d, %d\n", s[i].id, s[i].score);
    }

    /*Pass this array along with n to the sort() function*/
    sort(s, n);
    
    /*Print the contents of the array of n students.*/
    for(int i = 0; i < 10; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
