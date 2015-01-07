/**********
** Program: A14E3.cpp
** Author: Aryan Aziz
** Description: Insertion sort function and prototype with different sets of values
** Input: none
** Output: sorted arrays
**********/

#include <iostream>

int integerArray[5] = {1, 5, 4, 3, 2};
double doubleArray[5] = {1.1, 1.5, 1.4, 1.3, 1.2};
char charArray[5] = {'a', 'e', 'd', 'c', 'b'};

template<class TYPE>
void sort(TYPE *x) {
	//While so that we run it over and over until all of the numbers are in their place. I guess this way isn't 100%, but it got the job done.
	while(x[0] > x[1] || x[1] > x[2] || x[2] > x[3] || x[3] > x[4]) {
		for(int i = 1; i < 5; i++) {
			int j;
			j = i;
			while(x[i] < x[j - 1] && x[j] > 0) { //While the current number is less than the number before it, and there is at least 1 number before it
				TYPE tmp;
				tmp = x[i]; //Set the current number to a temporary one
				x[j] = x[j - 1]; //Set the current position to the number in the position before it
				x[j - 1] = tmp; //Set the position before it with the original number
				j--; //Remove a j
				//This basically swaps 2 numbers 1 at a time until they are in their specified place.
			}
		}
	}
}

/*void sort(int *x) {
	//While so that we run it over and over until all of the numbers are in their place. I guess this way isn't 100%, but it got the job done.
	while(x[0] > x[1] || x[1] > x[2] || x[2] > x[3] || x[3] > x[4]) {
		for(int i = 1; i < 5; i++) {
			int j;
			j = i;
			while(x[i] < x[j - 1] && x[j] > 0) { //While the current number is less than the number before it, and there is at least 1 number before it
				int tmp;
				tmp = x[i]; //Set the current number to a temporary one
				x[j] = x[j - 1]; //Set the current position to the number in the position before it
				x[j - 1] = tmp; //Set the position before it with the original number
				j--; //Remove a j
				//This basically swaps 2 numbers 1 at a time until they are in their specified place.
			}
		}
	}
};*/



int main() {
	sort(integerArray);
	sort(doubleArray);
	sort(charArray);

	for(int i = 0; i < 5; i++) {
		std::cout << integerArray[i] << " ";
	}

	std::cout << std::endl;

	for(int i = 0; i < 5; i++) {
		std::cout << doubleArray[i] << " ";
	}

	std::cout << std::endl;

	for(int i = 0; i < 5; i++) {
		std::cout << charArray[i] << " ";
	}

	return 0;
}