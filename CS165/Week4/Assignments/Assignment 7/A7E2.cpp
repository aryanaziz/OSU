/**********
** Program: A7E2.cpp
** Author: Aryan Aziz
** Description: Takes in 5 integers and outputs which is the largest and which is the smallest. 
** Input: array[](int)
** Output: Which value is the largest and smallest.
**********/

#include <iostream>
#include <limits>

int highest;
int lowest;

void exerciseTwo(void) {
	int *array;
	array = new int[5];

	for(int i = 0; i < 5; i++){ //The input loop
		std::cout << "Please enter an integer: ";
		std::cin >> array[i];
		while(std::cin.fail()){ //Checks if the value is an integer
			std::cout << "That is not a valid integer. Please re-enter an integer: ";
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cin >> array[i];
		}
	}

	highest = array[0];
	lowest = array[0];

	for(int i = 0; i < 5; i++){
		if(array[i] > highest){
			highest = array[i]; //Set the highest value
		}
	}

	for(int i = 0; i < 5; i++){
		if(array[i] < lowest){
			lowest = array[i]; //Set the lowest value
		}
	}
}


int main() {
	exerciseTwo();
	
	std::cout << highest << " " << lowest << std::endl;
	return 0;
}