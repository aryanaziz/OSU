/**********
** Program: A10E1.cpp
** Author: Aryan Aziz
** Description: Takes in a string and reverses the order and outputs the reversed string. 
** Input: inputString(string)
** Output: The reversed string. 
**********/

#include <iostream>
#include <string>

std::string inputString;
std::string outputString = "";

std::string reverse(std::string inputString) {
    for(int i = inputString.length() - 1; i > -1; i--) { //Go through the original string backwards
        outputString = outputString + inputString[i]; //Set the old string to add the value each time
    }

    return outputString;
}

int main() {
    std::cout << "Please enter a string: ";
    getline(std::cin, inputString);    

    std::cout << "The reversed string is: " << reverse(inputString) << std::endl;


    return 0;
}