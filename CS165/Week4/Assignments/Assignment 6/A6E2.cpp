/**********
** Program: A6E2.cpp
** Author: Aryan Aziz
** Description: Compares the C-Style strings and returns if they are the same or not. 
** Input: none (There was nothing in the assignment about inputs)
** Output: If the strings are the same. 
**********/

#include <iostream>
#include <string>
#include <cstring>

char szString1[] = "String";
char szString2[] = "String";

std::string checkStrings(char * x, char * y) {
	if (strcmp(x, y) == 0){
		return "The strings are the same!\n";
	}
	else {
		return "The strings are different!\n";
	}
}

//C-Style Strings are so much worse than normal strings...

int main() {

	std::cout << checkStrings(szString1, szString2);

	return 0;
}