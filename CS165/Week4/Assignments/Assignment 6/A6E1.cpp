/**********
** Program: A6E1.cpp
** Author: Aryan Aziz
** Description: Takes in 5 integer values and places them into an array 
** Input: input1(int), input2(int), input3(int), input4(int)
** Output: Sum of the values in the array
**********/

#include <iostream>
int input1, input2, input3, input4, input5;

int createArray(int input1, int input2, int input3, int input4, int input5) {
	int theArray[5] = { input1, input2, input3, input4, input5 };
	return theArray[0] + theArray[1] + theArray[2] + theArray[3] + theArray[4];
}

int main() {
	std::cout << "Enter 5 values: " << std::endl;
	std::cout << "Enter Value 1: ";
	std::cin >> input1;
		while(std::cin.fail()){
			std::cout << "That is not a valid integer. Please re-enter an integer: ";
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cin >> input1;
		}
	std::cout << "Enter Value 2: ";
	std::cin >> input2;
		while(std::cin.fail()){
			std::cout << "That is not a valid integer. Please re-enter an integer: ";
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cin >> input2;
		}
	std::cout << "Enter Value 3: ";	
	std::cin >> input3;
		while(std::cin.fail()){
			std::cout << "That is not a valid integer. Please re-enter an integer: ";
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cin >> input3;
		}
	std::cout << "Enter Value 4: ";
	std::cin >> input4;
		while(std::cin.fail()){
			std::cout << "That is not a valid integer. Please re-enter an integer: ";
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cin >> input4;
		}
	std::cout << "Enter Value 5: ";
	std::cin >> input5;
		while(std::cin.fail()){
			std::cout << "That is not a valid integer. Please re-enter an integer: ";
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cin >> input5;
		}

	std::cout << "The sum of the values in the array is: " << createArray(input1, input2, input3, input4, input5) << std::endl;

	return 0;
}