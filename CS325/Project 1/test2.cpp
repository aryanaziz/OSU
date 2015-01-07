/**********
** Program: 
** Author: Aryan Aziz
** Description:
** Input: 
** Output: 
**********/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>

const int arraySize = 100;

void subArray(int arr[], int size) {
	std::clock_t start; //Begin the timer
	double duration; //for the timer
	start = std::clock(); //for the timer
	int currentSum;
	int bestSum = 10000;
	int iLocation;
	int jLocation;
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			int k = i;
			while(k <= j) {
				if(k == i) {
					currentSum = arr[i];
				}
				else {
					currentSum = currentSum + arr[k];
				}
				k++;
			}
			if(abs(currentSum) < abs(bestSum) || abs(currentSum) == 0) {
				bestSum = abs(currentSum);
				iLocation = i;
				jLocation = j;
			}
		}
	}
	duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	std::cout << "1st Algorithm Duration: " << duration << std::endl;
	//std::cout << "Best Sum: " << bestSum << std::endl;
	//std::cout << "iLocation: " << iLocation << " " << arr[iLocation] << std::endl;
	//std::cout << "jLocation: " << jLocation << " " << arr[jLocation] << std::endl;
}

void subArrayTwo(int arr[], int size) {
	std::clock_t start; //Begin the timer
	double duration; //for the timer
	start = std::clock(); //for the timer
	int currentSum;
	int bestSum = 10000;
	int iLocation;
	int jLocation;
	for(int i = 0; i < size; i++) {
		currentSum = arr[i];
		for(int j = i; j < size; j++) {
			if(i == j) {
				currentSum = currentSum;
			}
			else {
				currentSum = currentSum + arr[j];
			}	
			if(abs(currentSum) < abs(bestSum) || abs(currentSum) == 0) {
				bestSum = abs(currentSum);
				iLocation = i;
				jLocation = j;
			}
			//std::cout << i << " " << j << " " << currentSum << std::endl;
		}
	}
	duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	std::cout << "2nd Algorithm Duration: " << duration << std::endl;
	//std::cout << "Best Sum: " << bestSum << std::endl;
	//std::cout << "iLocation: " << iLocation << " " << arr[iLocation] << std::endl;
	//std::cout << "jLocation: " << jLocation << " " << arr[jLocation] << std::endl;
}

int main(int argc, char* argv[]) {
	int array[arraySize];
	int n = sizeof(array) / sizeof(array[0]);

	for(int j = 0; j < 10; j++) {
		srand((unsigned)time(0));
		for(int i = 0; i < arraySize; i++) {
			array[i] = rand() % 1999 + (-999);
		
		}
		//subArray(array, n);
		subArrayTwo(array, n);
	}

	/*srand((unsigned)time(0));
	for(int i = 0; i < arraySize; i++) {
		array[i] = rand() % 1999 + (-999);
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;


	subArray(array, n);
	subArrayTwo(array, n);*/

	return 0;
}
