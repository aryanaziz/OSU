/**********
** Program: pp3-13.cpp
** Author: Aryan Aziz
** Description: Picks 4 unique numbers out of 25 to award prizes to. 
** Input: none
** Output: Prize Winners
**********/

#include <iostream>
#include <cstdlib>

int number1;
int number2;
int number3;
int number4;

//Random Number Generator Function (because why not)
int generateRandomNum(void){
	return rand() % 24 + 1; //Generate random number between 1 and 25
}

int main(){
	srand(time(0)); //Seed the random function

	number1 = generateRandomNum(); //Generate the 1st random number
	number2 = generateRandomNum(); //Generate the 2nd random number
	while(number2 == number1){ //If the 2nd number is the same as the first 
		number2 = generateRandomNum(); //Generate a new 2nd number
	}
	number3 = generateRandomNum(); //Generate the 3rd random number
	while(number3 == number2 || number3 == number1){ //If the 3rd number is the same as the 1st or 2nd
		number3 = generateRandomNum(); //Generate a new 3rd number
	}
	number4 = generateRandomNum(); //Generate the 4th random number
	while(number4 == number3 || number4 == number2 || number4 == number1){ //If the 4th number is the same as the 1st, 2nd, or 3rd
		number4 = generateRandomNum(); //Generate a new 4th number
	}

	std::cout << "Your winners are: " << std::endl << "Finalist Number " << number1 << std::endl << "Finalist Number " << number2 << std::endl << "Finalist Number " << number3 << std::endl << "Finalist Number " << number4 << std::endl;

	return 0;
}