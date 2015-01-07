/**********
** Program: A9E1.cpp
** Author: Aryan Aziz
** Description: Exercise 1. Classes. 
** Input: name(char[20]), age(int)
** Output: User's age. 
**********/

#include <iostream>
#include <string>

class person{
	public:
		char name[20];
		int age;
};

person newPerson() {
	person newPerson;
	std::cout << "Please enter a name: ";
	std::cin >> newPerson.name;
	std::cout << "Please enter an age: ";
	std::cin >> newPerson.age;
	return newPerson;
}

int main() {

	std::cout << newPerson().age;

	return 0;
}