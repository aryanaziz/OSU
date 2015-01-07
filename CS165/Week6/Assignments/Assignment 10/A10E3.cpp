/**********
** Program: A10E3.cpp
** Author: Aryan Aziz
** Description: Takes in an input string and checks if it's a plaindrome
** Input: inputString(string)
** Output: Whether it's a palindrome or not. 
**********/

#include <iostream>
#include <string>

std::string inputString;

bool is_palindrome(std::string inputString) {
	int i = 0; //Start at the beginning
	int j = inputString.length() - 1; //Start at the end

	while(i <= j) {
		if(inputString[i] != inputString[j]) { //Just check if they don't match. Otherwise it's good. 
			return false;
		}
		i++;
		j--;
	}

	return true;
}

int main() {
    std::cout << "Please enter a string: ";
    getline(std::cin, inputString);

    if(is_palindrome(inputString) == 1) {
    	std::cout << "The string, " << inputString << " is a palindrome!" << std::endl;
    }    

    else {
    	std::cout << "The string, " << inputString << " is not a palindrome!" << std::endl;
    }

    return 0;
}