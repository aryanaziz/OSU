/**********
** Program: pp13-10.cpp
** Author: Aryan Aziz
** Description: Returns the total number of bowling pins. 
** Input: n(int)
** Output: Total number of bowling pins. 
**********/

#include <iostream>

int n;

int pins(int n){
	if(n == 1){
		return 1;
	}
	else{
		return (n + pins(n-1));
	}
}

int main(){
	std::cout << "Please enter the number of rows: ";
	std::cin >> n;

	std::cout << "The total number of pins for " << n << " rows is: " << pins(n) << std::endl;
	return 0;
}