/**********
** Program: A10E2.cpp
** Author: Aryan Aziz
** Description: Takes in a string and reverses the order and outputs the reversed string. 
** Input: inputString(string)
** Output: The reversed string. 
**********/

#include <iostream>
#include <string>

std::string inputString;

std::string reverse(std::string inputString) {
	if(inputString.length() == 1) { //Our base case
		return inputString;
	}
	else {
		return reverse(inputString.substr(1, inputString.length())) + inputString.at(0);
	}
}

int main() {
    std::cout << "Please enter a string: ";
    getline(std::cin, inputString);    

    std::cout << "The reversed string is: " << reverse(inputString) << std::endl;


    return 0;
}