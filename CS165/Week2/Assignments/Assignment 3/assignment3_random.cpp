/**********
** Program: assignment3_random.cpp
** Author: Aryan Aziz
** Description: Output 10 random numbers to the console
** Input: none
** Output: random numbers
**********/

#include <iostream>
#include <cstdlib>

int randomNumber;


int generateRandomNumber(void){
	srand(time(0));
	randomNumber = rand() % 10000;
	return randomNumber;
}

int main(){
	for(int i = 0; i < 10; i++){
		std::cout << generateRandomNumber() << std::endl;
	}
	return 0;
}