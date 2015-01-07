/**********
** Program: A13E4.cpp
** Author: Aryan Aziz
** Description: Grabs the integer from a string. 
** Input: input(std::string)
** Output: the integer.
**********/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::string input;
std::string theIntegerString;
int theInteger;
std::string numbers = "0123456789";
std::stringstream ss;
std::vector<int> foundNumbers;
int length = 1;

int doTheThang(void) {

	do {
		std::cout << "Please enter an integer: ";
		getline(std::cin, input);

		std::size_t found = input.find_first_of(numbers.c_str());

		while (found != std::string::npos) {
			foundNumbers.push_back(found);
			found = input.find_first_of(numbers.c_str(), found+1);
		}
	} while (foundNumbers.size() < 1);


	for(int i = 0; i < foundNumbers.size(); i++) {
		if(foundNumbers[i] + 1 == foundNumbers[i+1]) {
			length++;
		}
	}

	theIntegerString = input.substr(foundNumbers[0], length);

	ss << theIntegerString;
	ss >> theInteger;
	ss.str("");
	ss.clear();

	return theInteger;
}



int main() {

	std::cout << doTheThang() << std::endl;

	return 0;
}