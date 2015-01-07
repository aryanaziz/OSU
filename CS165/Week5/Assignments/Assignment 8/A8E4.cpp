/**********
** Program: A8E4.cpp
** Author: Aryan Aziz
** Description: Exercise 4, playing with structs and pointers to them. 
** Input: N/A
** Output: Various items for testing. 
**********/

#include <iostream>
#include <string>

struct person {
	std::string name;
	int age;
};


int main() {
	struct person *p_person;
	struct person newPerson;
	p_person = &newPerson;

	p_person->age = 23;

	std::cout << p_person << std::endl;
	std::cout << newPerson.age << std::endl;


	person friends[5];
	friends[1].name = "Friend 1";
	friends[1].age = 20;
	friends[2].name = "Friend 2";
	friends[2].age = 21;
	friends[3].name = "Friend 3";
	friends[3].age = 22;
	friends[4].name = "Friend 4";
	friends[4].age = 23;
	friends[5].name = "Friend 5";
	friends[5].age = 24;

	std::cout << friends[1].age << std::endl;

	return 0;
}