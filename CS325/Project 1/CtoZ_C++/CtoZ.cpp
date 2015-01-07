/**********
** Program: CtoZ.cpp
** Author: Aryan Aziz - Bryon Burleigh
** Description: Takes in an input txt file, and finds the subarray of each line that is the closest to zero. 
** Input: whichever text file you specify in command line
** Output: subarray1.txt and subarray2.txt
**********/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>

//Define the array size, change this if you want an input array bigger than 100 integers
const int arraySize = 100;

//First algorithm
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
	std::cout << "Best Sum: " << bestSum << std::endl;
	std::cout << "iLocation: " << iLocation << " " << arr[iLocation] << std::endl;
	std::cout << "jLocation: " << jLocation << " " << arr[jLocation] << std::endl;

	//Once we find an answer, output it to file
	std::ofstream ofs;
	std::string fileName = "subarray1.txt";
	ofs.open(fileName.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app);
	ofs << "[";
	for(int i = 0; i < size; i++) {
		if(i == size - 1) {
			ofs << arr[i];
		}
		else {
			ofs << arr[i] << ",";
		}
	}
	ofs << "], [";
	for(int i = iLocation; i <= jLocation; i++) {
		if(i == jLocation) {
			ofs << arr[i];
		}
		else {
			ofs << arr[i] << ",";
		}
	}
	ofs << "]," << bestSum << "\r\n";
}

//2nd Algorithm
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
		}
	}
	duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	std::cout << "Best Sum: " << bestSum << std::endl;
	std::cout << "iLocation: " << iLocation << " " << arr[iLocation] << std::endl;
	std::cout << "jLocation: " << jLocation << " " << arr[jLocation] << std::endl;

	//Once we have an answer, output to file. 
	std::ofstream ofs;
	std::string fileName = "subarray2.txt";
	ofs.open(fileName.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app);
	ofs << "[";
	for(int i = 0; i < size; i++) {
		if(i == size - 1) {
			ofs << arr[i];
		}
		else {
			ofs << arr[i] << ",";
		}
	}
	ofs << "], [";
	for(int i = iLocation; i <= jLocation; i++) {
		if(i == jLocation) {
			ofs << arr[i];
		}
		else {
			ofs << arr[i] << ",";
		}
	}
	ofs << "]," << bestSum << "\r\n";
}

int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cout << "Please append a file name when running!" << std::endl;
		return 0;
	}


	//File Input
	std::ifstream ifs;
	ifs.open(argv[1]);

	std::string line;
	int array[arraySize];

	while(!ifs.eof()) {
		getline(ifs, line); //Get the line and save it to a string
		int stringSize = line.length(); //Set the length
		line = line.substr(1, stringSize - 2); //Remove the beginning and end [ ]
		
		std::istringstream input(line); //start stringstream
		std::string number;
		std::vector<int> ints; //Create a vector of ints
		while(std::getline(input, number, ',')) {
			std::istringstream iss(number);
			int i;
			iss >> i;
			ints.push_back(i); //Place it into the vector
		}
		std::copy(ints.begin(), ints.end(), array); //Convert from vector to array
		int n = sizeof(array) / sizeof(array[0]);
		subArray(array, n); //Run the first algorithm
		subArrayTwo(array, n); //Run the 2nd algorithm
	}
	//End File Input
	return 0;
}
