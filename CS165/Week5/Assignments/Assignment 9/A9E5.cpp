/**********
** Program: A9E5.cpp
** Author: Aryan Aziz
** Description: Exercise 5. Fun with classes and pointers!
** Input: None. 
** Output: Various for testing. 
**********/

#include <iostream>
#include <string>

class person {
	public:
		std::string name;
		int age;
};


int main() {
	person *p_person;
	person newPerson;
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

	person *friend_ptrs[5];

	for(int i = 0; i < 5; i++){
		friend_ptrs[i] = &friends[i];
	}

	std::cout << friend_ptrs[1]->age << std::endl;

	return 0;
}