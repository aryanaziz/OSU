/**********
** Program: A7E5.cpp
** Author: Aryan Aziz
** Description: Takes in 5 integers and displays which one is the largest and smallest. 
** Input: a(command line int), b(command line int), c(command line int), d(command line int), e(command line int)
** Output: Highest and Smallest Values
**********/

#include <iostream>
#include <limits>
#include <cstdlib>

int highest;
int lowest;
int a;
int b;
int c; 
int d; 
int e;

void exerciseTwo( int a, int b, int c, int d, int e) {
	int *array; //Create the dynamic array
	array = new int[5];

	array[0] = a; //Set the values
	array[1] = b;
	array[2] = c;
	array[3] = d;
	array[4] = e;

	highest = array[0];
	lowest = array[0];

	for(int i = 0; i < 5; i++){
		if(array[i] > highest){
			highest = array[i]; //Set the value to the highest value
		}
	}

	for(int i = 0; i < 5; i++){
		if(array[i] < lowest){
			lowest = array[i]; //Set the value to the lowest value
		}
	}
}


int main( int argc, char *argv[] ) {
	a = std::atoi(argv[1]); //Convert the values from a character to an integer
	b = std::atoi(argv[2]);
	c = std::atoi(argv[3]);
	d = std::atoi(argv[4]);
	e = std::atoi(argv[5]);

	exerciseTwo(a, b, c, d, e); //Pass all the values over

	std::cout << highest << " " << lowest << std::endl;
	return 0;
}