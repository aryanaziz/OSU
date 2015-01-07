/**********
** Program: assignment5-1.cpp
** Author: Aryan Aziz
** Description: Requests a range and creates a random number within that range
** Input: minRange(int), maxRange(int)
** Output: Random number within the specified range
**********/

#include <iostream>
#include <cstdlib>
#include <limits>

const int minRange = 1;
const int maxRange = 1000;
int randomNum;

void rand_int(const int &minRange, const int &maxRange, int &randomNum){
	srand(time(0)); //Seeds the rand function
	randomNum = rand() % (maxRange - minRange) + minRange;
}


int main(){
	rand_int(minRange, maxRange, randomNum);
	std::cout << "Your random number between " << minRange << "-" << maxRange << " is: " << randomNum << std::endl;

	return 0;
}