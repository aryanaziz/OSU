/**********
** Program: A7E1.cpp
** Author: Aryan Aziz
** Description: Takes in a pointer and changes the variable. 
** Input: y(int)
** Output: variable.
**********/

#include <iostream>
int y;

void exerciseOne(int *x){ //Function taking in a pointer
	std::cin >> y;
	*x = y; //Set the original referenced/pointer to the value
}

int main() {
	int variable; 

	exerciseOne(&variable); //Passing the variable reference

	std::cout << variable << std::endl;


	return 0;
}