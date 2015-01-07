/**********
** Program: assignment4_string_function.cpp
** Author: Aryan Aziz
** Description: Includes question 2 from Assignment 4
** Input: minRange(int), maxRange(int)
** Output: A random number between 2 values
**********/

#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>

int minRange;
int maxRange;
int randomNum;

int rand_int(int minRange, int maxRange){
	srand(time(0)); //Seeds the rand function so that a different random number is chosen every second (otherwise the same random number will popup for the same range)
	randomNum = rand() % (maxRange - minRange) + minRange; //Creates a random number
	return randomNum; //Returns that number
}

int main(){
	std::cout << "Please enter an integer greater than 1 as your minimum range: ";
	std::cin >> minRange;

	while(minRange < 1){ //Checks to see if the value was an int/double. If it was a string/char then minRange == -1
		std::cout << "I'm sorry, that was not an integer greater than 1. Please enter an integer greater than 1 for your minimum range: ";
		std::cin.clear(); //Clears the error flag on the cin so that future operations will work flawlsy
    	std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n'); //Skips to the next new line to ignore everything else on the current line
		std::cin >> minRange; //Ask for the input again
	}

	std::cout << "Please enter an integer greater than " << minRange << " as your maximum range: ";
	std::cin >> maxRange;

	while(maxRange <= minRange){ //If the maxRange is less than or equal to the minRange (will cover all bad types of maxRange)
		if(maxRange < 1){ //If the maxRange is less than 1 (if it was a string/char)
			std::cout << "I'm sorry, that was not a valid integer. Please enter an integer greater than " << minRange << " for your maximum range: ";
			std::cin.clear(); //Clears the error flag on the cin so that future operations will work flawlsy
    		std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n'); //Skips to the next new line to ignore everything else on the current line
			std::cin >> maxRange;
		}
		if(maxRange > 1 && maxRange <= minRange){ //If the maxRange is an int but it's less than or equal to the minRange
			std::cout << "I'm sorry, that was not an integer greater than " << minRange << ". Please enter an integer greater than " << minRange << " for your minimum range: ";
			std::cin >> maxRange; //No need for ignore/clear here because it's just adding another in to the line

		}
	}

	rand_int(minRange, maxRange);

	std::cout << "Your random number between " << minRange << "-" << maxRange << " is: " << randomNum << std::endl;

	return 0;
}