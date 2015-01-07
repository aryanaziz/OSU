/**********
** Program: A10E4.cpp
** Author: Aryan Aziz
** Description: Checks if the string is a palindrome or note.  
** Input: inputString(string)
** Output: Whether the string is a palindrome. 
**********/

#include <iostream>
#include <string>

std::string inputString;

bool is_palindrome(std::string inputString, int start, int end) {

	if(end <= 1) {
		return true; //Base Case
	}

	else if(inputString[start] == inputString[end]) {
		return is_palindrome(inputString, start + 1, end - 1);
	}

	else {
		return false;
	}
}

int main() {
    std::cout << "Please enter a string: ";
    getline(std::cin, inputString);

    int start = 0;
    int end = inputString.length() - 1;

    if(is_palindrome(inputString, start, end) == 1) {
    	std::cout << "The string, '" << inputString << "' is a palindrome!" << std::endl;
    }    

    else {
    	std::cout << "The string, '" << inputString << "' is not a palindrome!" << std::endl;
    }    


    return 0;
}