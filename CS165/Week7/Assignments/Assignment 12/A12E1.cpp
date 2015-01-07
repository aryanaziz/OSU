/**********
** Program: A12E1.cpp
** Author: Aryan Aziz
** Description: Recursively calls a function until it gets to a specified depth and throws an exception.
** Input: none
** Output: The exception level
**********/

#include <iostream>
#include <stdexcept>

int level = 0;

void digDeep(int throwLevel) throw (int) {
	if(level == throwLevel) {
		throw level;
	}
	else {
		std::cout << "We have currently gone " << level << " level(s) deep!" << std::endl;
		level++;
		digDeep(throwLevel);
	}
}


int main()
{
    int throwLevel = 10;

    try
    {
        digDeep(throwLevel);
    }
    catch(int e)
    {
        std::cout << "We went " << e << " level(s) deep and have thrown an exception." << std::endl;
    }

    return 0;
}

