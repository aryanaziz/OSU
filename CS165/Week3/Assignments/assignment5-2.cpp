/**********
** Program: assignment5-2.cpp
** Author: Aryan Aziz
** Description: Requests 2 strings and returns whether they are the same. 
** Input: firstString(str), secondString(str)
** Output: If strings are the same or not. 
**********/

#include <iostream>
#include <string>

std::string firstString;
std::string secondString;

void compareString(std::string &firstString, std::string &secondString){
	if(firstString == secondString){
		std::cout << "The strings match!" << std::endl;
	}

	else{
		std::cout << "The strings do not match!" << std::endl;
	}
}

int main(){
	std::cout << "Please enter your first string: ";
	getline(std::cin, firstString);
	std::cout << "Please enter your second string: ";
	getline(std::cin, secondString);


	compareString(firstString, secondString);

	return 0;
}