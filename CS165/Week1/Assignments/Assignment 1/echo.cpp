/**********
** Program: echo.cpp
** Author: Aryan Aziz
** Description: Requests a number and echos it back to the user
** Input: x(int)
** Output: x
**********/

#include <iostream>

int x;
int main() {
	std::cout << "Hello! Please enter a whole number followed by <enter>\n";
	std::cin >> x;

	std::cout << "You have entered " << x << "\n";

	return 0;
}