/**********
** Program: A8E5.cpp
** Author: Aryan Aziz
** Description: Exercise 5
** Input: Playing with multi-leveled pointered structs. 
** Output: Various testing ones. 
**********/

#include <iostream>
#include <string>

struct person {
	std::string name;
	int age;
};


int main() {

	int n = 5;

	person **ptr=new person *[n];

	for(int i = 0; i < n; i++) {
		ptr[i] = new person;
	}

	ptr[2]->name = "Test";

	std::cout << ptr[2]->name;

	for(int i = 0; i < n; ++i) {
	    delete ptr[i];
	}
	delete [] ptr;
	return 0;
}