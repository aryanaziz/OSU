/**********
** Program: assignment3_strings.cpp
** Author: Aryan Aziz
** Description: Prints the string 1 by 1 from front to back, back to front, and then counts the number of letters in the string and outputs that.
** Input: my_str(string)
** Output: String 1 by 1, length
**********/

#include <iostream>
#include <string>

std::string my_str;
int length;

int main(){
	std::cin >> my_str;

	/*for (int i = 0; i < my_str.length(); i++){ //1 by 1 from front to back
		std::cout << my_str.at(i) << std::endl;
	}*/

	/*for (int x = my_str.length() - 1; x >= 0; x--){ //1 by 1 from back to front. Using length-1 because length doesn't start at 0, starts at 1
		std::cout << my_str.at(x) << std::endl;
	}*/

	for (int i = 0; i < my_str.length(); i++){
		length++;
	}

	std::cout << length++;	


	return 0;
}