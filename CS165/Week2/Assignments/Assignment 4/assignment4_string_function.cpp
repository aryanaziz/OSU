/**********
** Program: assignment4_string_function.cpp
** Author: Aryan Aziz
** Description: Includes question 1 from Assignment 4
** Input: firstString(string), secondString(string)
** Output: If 2 strings are the same
**********/

#include <iostream>
#include <string>

std::string firstString;
std::string secondString;

void compareString(void){
	std::cout << "Please enter your first string: ";
	getline(std::cin, firstString);
	std::cout << "Please enter your second string: ";
	getline(std::cin, secondString);

	if(firstString == secondString){
		std::cout << "The strings match!" << std::endl;
	}

	else{
		std::cout << "The strings do not match!" << std::endl;
	}
}

int main(){
	compareString();

	return 0;
}