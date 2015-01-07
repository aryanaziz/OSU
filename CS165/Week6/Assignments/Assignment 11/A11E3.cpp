/**********
** Program: A11E3.cpp
** Author: Aryan Aziz
** Description: Multiplies 2 arrays and sets the values in the 3rd 
** Input: none
** Output: the array's value at various positions
**********/

#include <iostream>

int array1[10][10];
int array2[10][10];
int array3[10][10];

void fillArray1(void) {
	for(int i = 0; i < 10; i++) {
		for(int n = 0; n < 10; n++) {
			array1[i][n] = 2;
		}
	}
}

void fillArray2(void) {
	for(int i = 0; i < 10; i++) {
		for(int n = 0; n < 10; n++) {
			array2[i][n] = 5;
		}
	}
}

void arrayMultiplication(int array1[10][10], int array2[10][10], int array3[10][10]) {
	for(int i = 0; i < 10; i++) {
		for(int n = 0; n < 10; n++) {
			array3[i][n] = array1[i][n] * array2[i][n];
		}
	}
}

int main() {

	fillArray1();
	fillArray2();
	
	arrayMultiplication(array1, array2, array3);

	std::cout << array3[5][5] << std::endl << array3[7][7];


	return 0;
}

