/**********
** Program: A11E4.cpp
** Author: Aryan Aziz
** Description: Outputs the sum of all numbers that are multiples of various numbers.  
** Input: none
** Output: The sums
**********/

#include <iostream>

int number;
int number1;
int number2;

int calculateSumSingle(int number) {
	int x = 0;
	for(int i = 1; i <= 1000; i++) {
		if(i % number == 0) {
			x = x + i;
		}
	}

	return x;
}

int calculateSumMultiple(int number1, int number2) {
	int x = 0;
	for(int i = 1; i <= 1000; i++) {
		if(i % number1 == 0) {
			x = x + i;
		}
		if(i % number2 == 0) {
			x = x + i;
		}
	}

	return x;
}

int main() {

	std::cout << "The sum of all numbers between 1-1000 that are divisible by 3 = " << calculateSumSingle(3) << std::endl;
	std::cout << "The sum of all numbers between 1-1000 that are divisible by 5 = " << calculateSumSingle(5) << std::endl;
	std::cout << "The sum of all numbers between 1-1000 that are divisible by 3 or 5 = " << calculateSumMultiple(3, 5) << std::endl;
	return 0;
}