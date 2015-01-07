/**********
** Program: A10E5.cpp
** Author: Aryan Aziz
** Description: Let's the user choose what they want to do and either checks if it's a palindrome or reverses the string.   
** Input: inputString(string), whatFunction(string), functionType(string), menuSelection(string)
** Output: Specified function results. 
**********/

#include <iostream>
#include <string>

std::string inputString;
std::string whatFunction;
std::string functionType;
std::string outputString;
std::string menuSelection;

bool is_palindrome_recursive(std::string inputString, int start, int end) {

	if(end <= 1) {
		return true;
	}

	else if(inputString[start] == inputString[end]) {
		return is_palindrome_recursive(inputString, start + 1, end - 1);
	}

	else {
		return false;
	}
}

bool is_palindrome_iterative(std::string inputString) {
    int i = 0;
    int j = inputString.length() - 1;

    while(i <= j) {
        if(inputString[i] != inputString[j]) {
            return false;
        }
        i++;
        j--;
    }

    return true;
}

std::string reverse_iterative(std::string inputString) {
    for(int i = inputString.length() - 1; i > -1; i--) {
        outputString = outputString + inputString[i];
    }

    return outputString;
}

std::string reverse_recursive(std::string inputString) {
    if(inputString.length() == 1) {
        return inputString;
    }
    else {
        return reverse_recursive(inputString.substr(1, inputString.length())) + inputString.at(0);
    }
}

void menu(void) {
    std::cout << "What would you like to do?" << std::endl << "A: Reverse a String" << std::endl << "B: Check For a Palindrome" << std::endl;
    std::cin >> whatFunction;

    while(whatFunction.length() > 1 || whatFunction.length() < 1) {
        std::cout << "That is not a valid input, please enter 'A' or 'B'" << std::endl;
        std::cin >> whatFunction;
    }
    while(whatFunction[0] != 'A' && whatFunction[0] != 'a' && whatFunction[0] != 'B' && whatFunction[0] != 'b'){
        std::cout << "That is not a valid input, please enter 'A' or 'B'" << std::endl;
        std::cin >> whatFunction;
    }


    if(whatFunction[0] == 'A' || whatFunction[0] == 'a') {
        std::cout << "You have selected: A) Reverse a String" << std::endl << std::endl;
    }
    else {
        std::cout << "You have selected: B) Check for a Palindrome" << std::endl << std::endl;
    }


    std::cout << "Please select a function type:" << std::endl << "1: Iterative" << std::endl << "2: Recursive" << std::endl;
    std::cin >> functionType;

    while(functionType.length() > 1 || whatFunction.length() < 1) {
        std::cout << "That is not a valid input, please enter '1' or '2'" << std::endl;
        std::cin >> functionType;
    }
    while(functionType[0] != '1' && functionType[0] != '2') {
        std::cout << "That is not a valid input, please enter '1' or '2'" << std::endl;
        std::cin >> functionType;
    }


    if(whatFunction[0] == 'a') {
        whatFunction[0] = 'A';
    }
    if(whatFunction[0] == 'b') {
        whatFunction[0] = 'B';
    }

    menuSelection = whatFunction + functionType;
}

int main() {

    menu();
    std::cin.ignore();
    std::cout << "Please enter a string: ";
    getline(std::cin, inputString);

    if(menuSelection[0] == 'A') {
        if(menuSelection[1] == '1') {
            std::cout << "Your string '" << inputString << "' reversed is: " << reverse_iterative(inputString) << std::endl;
        }
        if(menuSelection[1] == '2') {
            std::cout << "Your string '" << inputString << "' reversed is: " << reverse_recursive(inputString) << std::endl;
        }
    }

    else {
        if(menuSelection[1] == '1') {
            if(is_palindrome_iterative(inputString) == 1) {
                std::cout << "The string '" << inputString << "' is a palindrome!" << std::endl;
            }
            else {
                std::cout << "The string '" << inputString << "' is not a palindrome!" << std::endl;
            }
        }
        if(menuSelection[1] == '2') {
            int start = 0;
            int end = inputString.length() - 1;
            if(is_palindrome_recursive(inputString, start, end) == 1) {
                std::cout << "The string '" << inputString << "' is a palindrome!" << std::endl;
            }
            else {
                std::cout << "The string '" << inputString << "' is not a palindrome!" << std::endl;
            }
        }
    }

    return 0;
}