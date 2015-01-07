/**********
** Program: assignment3_string_comparison.cpp
** Author: Aryan Aziz
** Description: Take 2 strings and compare them
** Input: firstString(string), secondString(string)
** Output: Whether they are the same or not.
**********/

#include <iostream>
#include <string>

std::string firstString;
std::string secondString;


int main(){
	getline(std::cin, firstString);
	getline(std::cin, secondString);

	if(firstString == secondString){
		std::cout << "They are the same!" << std::endl;
	}

	else{
		std::cout << "They are Different!" << std::endl;
	}
	return 0;
}