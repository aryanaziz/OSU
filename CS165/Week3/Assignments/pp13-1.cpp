/**********
** Program: pp13-1.cpp
** Author: Aryan Aziz
** Description: Returns the specified Fibonacci number. 
** Input: n(int)
** Output: Specified Fibonacci number. 
**********/

#include <iostream>

int n;

int fibonacci(int n){
	if(n == 1 || n == 0){
		return 1;
	}
	else {
		return fibonacci(n-2)+fibonacci(n-1);
	}
}

int main(){
	std::cout << "Please enter the position you would like the fibonacci number for: ";
	std::cin >> n;

	std::cout << "The fibonacci number at the " << n << "th spot is: " << fibonacci(n) << std::endl;
	return 0;
}