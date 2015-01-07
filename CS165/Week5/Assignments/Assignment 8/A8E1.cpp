/**********
** Program: A8E1.cpp
** Author: Aryan Aziz
** Description: Creates a struct and returns it for usage. 
** Input: newPerson.name(char[20]), newPerson.age(int)
** Output: To see it work, just the name.
**********/

#include <iostream>

struct person {
	char name[20];
	int age;
};

person new_person(void);

int main() {
	person personStruct;

	personStruct = new_person();

	std::cout << personStruct.name << std::endl;

	return 0;
}

person new_person(void) {
	person newPerson;

	std::cout << "Please enter a name: ";
	std::cin >> newPerson.name;
	std::cout << "Please enter an age: ";
	std::cin >> newPerson.age;

	return newPerson;
}