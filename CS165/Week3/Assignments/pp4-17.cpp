/**********
** Program: pp4-17.cpp
** Author: Aryan Aziz
** Description: Gets 3 integers from the user and re-arranges them so that the first variable becomes the smallest int, etc. 
** Input: a(int), b(int), c(int)
** Output: Random number within the specified range
**********/

#include <iostream>
#include <string>

int a;
int b; 
int c;
int lowest;
int middle;
int highest;

void sort(int &a, int &b, int &c){
	lowest = a;
	if(b < lowest){
		lowest = b;
	}
	if(c < lowest){
		lowest = c;
	}
	highest = a;
	if(b > highest){
		highest = b;
	}
	if(c > highest){
		highest = c;
	}
	if(lowest == a){
		if(highest == b){
			middle = c;
		}
		if(highest == c){
			middle = b;
		}
	}
	if(lowest == b){
		if(highest == a){
			middle = c;
		}
		if(highest == c){
			middle = a;
		}
	}
	if(lowest == c){
		if(highest == a){
			middle = b;
		}
		if(highest == b){
			middle = a;
		}
	}
	a = lowest;
	b = middle;
	c = highest;
}


int main(){
	std::cout << "Please enter your first value: ";
	std::cin >> a;

	std::cout << "Please enter your second value: ";
	std::cin >> b;

	std::cout << "Please enter your third value: ";
	std::cin >> c;

	sort(a, b, c);


	std::cout << "Lowest value: " << a << std::endl << "Middle value: " << b << std::endl << "Highest value: " << c << std::endl;
	return 0;
}