/* CS261- Assignment 1 - Q.1*/
/* Name: Aryan Aziz
 * Date: 6-29-14
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student* s = malloc(10 * sizeof(struct student));

     /*return the pointer*/
     return s;
}

void generate(struct student* students){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
  for(int i = 1; i < 11; i++) {
    students[i].id = i;
    students[i].score = rand() % 101;
  }
     
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/

    for(int i = 1; i < 11; i++) {
      printf("%d, %d\n", students[i].id, students[i].score);
    }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
    int minimum = 100;
    int maximum = 0;
    int averageSum = 0;
    int average;

    for(int i = 1; i < 11; i++) {
      if(students[i].score < minimum) {
        minimum = students[i].score;
      }

      if(students[i].score > maximum) {
        maximum = students[i].score;
      }

      averageSum = averageSum + students[i].score;
    }

    average = averageSum / 10;

    printf("The minimum is: %d\n", minimum);
    printf("The maximum is: %d\n", maximum);
    printf("The average is: %d\n", average);
     
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    free(stud);
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);
    
    /*call deallocate*/

    return 0;
}
