/**********
** Program: A9E2.cpp
** Author: Aryan Aziz
** Description: Exercise 2, fun with classes!
** Input: None
** Output: The user's age after a birthday. 
**********/

#include <iostream>
#include <string>

class person{
	public:
		char name[20];
		int age;
		int having_birthday(void) {
			return age++;
		}
};

person newPerson() {
	person newPerson;
	std::cout << "Please enter a name: ";
	std::cin >> newPerson.name;
	std::cout << "Please enter an age: ";
	std::cin >> newPerson.age;

	newPerson.having_birthday();
	return newPerson;
}

int main() {

	std::cout << newPerson().age << std::endl;



	return 0;
}