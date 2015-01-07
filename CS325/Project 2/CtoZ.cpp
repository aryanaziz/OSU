/**********
** Program: CtoZ.cpp
** Author: Aryan Aziz - Bryon Burleigh - Joni Carlson
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
#include <cmath>
#include <algorithm>

//Define the array size, change this if you want an input array bigger than 100 integers
const int arraySize = 100;

int sizeOfArray = arraySize;
int bestSum = 10000;
int bestDistance = 10000;
int iLocation;
int jLocation;

//First algorithm
void firstAlgorithm(int firstArr[], int secondArr[]) {
	int currentSum;
	int bestSum = 10000;
	int iLocation;
	int jLocation;
	int firstArrSum = 0;
	int secondArrSum = 0;

	for(int i = arraySize - 1; i >= 0; i--) {
		firstArrSum += firstArr[i];
		secondArrSum = 0;
		for(int j = arraySize - 1; j >= 0; j--) {
			secondArrSum += secondArr[j];
			currentSum = firstArrSum + secondArrSum;
			if(abs(currentSum) < abs(bestSum) || abs(currentSum) == 0) {
				bestSum = abs(currentSum);
				iLocation = i;
				jLocation = j;
			}
		}
	}

	std::cout << "Best Sum: " << bestSum << std::endl;
	std::cout << "iLocation: " << iLocation << "[";
	firstArrSum = 0; 
	for(int i = iLocation; i <= arraySize - 1; i++) {
		firstArrSum += firstArr[i];
		std::cout << firstArr[i] << ",";
	}
	std::cout << "], " << firstArrSum << std::endl;
	std::cout << "jLocation: " << jLocation << "[";
	secondArrSum = 0;
	for(int i = jLocation; i <= arraySize - 1; i++) {
		secondArrSum += secondArr[i];
		std::cout << secondArr[i] << ",";
	}
	std::cout << "], " << secondArrSum << std::endl;
}

int firstSumAlgorithm(std::vector<int> vector, int low, int middle, int high) {
	int currentSum = 0;
	int firstArrSum = 0;
	int secondArrSum;


	for(int i = middle; i >= low; i--) {
		firstArrSum += vector.at(i);
		secondArrSum = 0;
		for(int j = middle + 1; j <= high; j++) {
			secondArrSum += vector.at(j);
			currentSum = firstArrSum + secondArrSum;
			if(abs(currentSum) < abs(bestSum)) {
				bestSum = abs(currentSum);
				iLocation = i;
				jLocation = j;
			}
		}
	}
	return bestSum;
}

//2nd Algorithm
void secondAlgorithm(int firstArr[], int secondArr[]) {
	std::vector<std::pair<int,int> > suffixArray;
	int firstArrSum = 0;
	int secondArrSum = 0;
	int bestDistance = 10000;


	int indexNumber = 0;

	for(int i = arraySize - 1; i >= 0; i--) {
		firstArrSum += firstArr[i];
		suffixArray.push_back(std::make_pair(firstArrSum,indexNumber));
		indexNumber++;
	}
	for(int j = arraySize - 1; j >= 0; j--) {
		secondArrSum += secondArr[j];
		suffixArray.push_back(std::make_pair(secondArrSum * -1,indexNumber));
		indexNumber++;
	}

	//0-49 = first array
	//50-99 = second array
	std::sort(suffixArray.begin(), suffixArray.end());

	for(int i = 0; i < suffixArray.size() - 1; i++) {
		for(int j = i+1; j < suffixArray.size(); j++) {
			int currentDistance = suffixArray.at(i).first - suffixArray.at(j).first;
			if(suffixArray.at(i).second <= 49 && suffixArray.at(j).second >= 50) { //If the first number is from the first array and second number from the second array
				if(abs(currentDistance) < abs(bestDistance) || abs(currentDistance) == 0) {
					bestDistance = currentDistance;
					iLocation = i;
					jLocation = j;
					break;
				}
			}
			else if(suffixArray.at(i).second >= 50 && suffixArray.at(j).second <= 49) { //If the first number is from the second array and second number from the first array
				if(abs(currentDistance) < abs(bestDistance) || abs(currentDistance) == 0) {
					bestDistance = currentDistance;
					iLocation = i;
					jLocation = j;
					break;
				}
			}
		}
	}

	int firstArrayIndex;
	int secondArrayIndex;
	if(suffixArray.at(iLocation).second < 49) {
		firstArrayIndex = (arraySize - 1) - suffixArray.at(iLocation).second;
	}
	if(suffixArray.at(jLocation).second < 49) {
		firstArrayIndex = (arraySize - 1) - suffixArray.at(jLocation).second;
	}
	if(suffixArray.at(iLocation).second > 50) {
		secondArrayIndex = (arraySize - 1) - (suffixArray.at(iLocation).second - 50);
	}
	if(suffixArray.at(jLocation).second > 50) {
		secondArrayIndex = (arraySize - 1) - (suffixArray.at(jLocation).second - 50);
	}

	std::cout << "iLocation: " << iLocation << " - " << firstArrayIndex << "[";
	firstArrSum = 0; 
	for(int i = firstArrayIndex; i <= arraySize - 1; i++) {
		firstArrSum += firstArr[i];
		std::cout << firstArr[i] << ",";
	}
	std::cout << "], " << firstArrSum << std::endl;

	std::cout << "jLocation: " << jLocation << " - " << secondArrayIndex << "[";
	secondArrSum = 0;
	for(int i = secondArrayIndex; i <= arraySize - 1; i++) {
		secondArrSum += secondArr[i];
		std::cout << secondArr[i] << ",";
	}
	std::cout << "], " << secondArrSum << std::endl;	
}

int secondSumAlgorithm(std::vector<int> vector, int low, int middle, int high) {
	std::vector<std::pair<int,int> > suffixArray;
	int firstArrSum = 0;
	int secondArrSum = 0;
	int indexNumber = 0;

	for(int i = middle; i >= low; i--) {
		firstArrSum += vector.at(i);
		suffixArray.push_back(std::make_pair(firstArrSum,indexNumber));
		indexNumber++;
	}
	for(int j = high; j > middle; j--) {
		secondArrSum += vector.at(j);
		suffixArray.push_back(std::make_pair(secondArrSum * -1,indexNumber));
		indexNumber++;
	}

	//0-49 = first array
	//50-99 = second array
	std::sort(suffixArray.begin(), suffixArray.end());

	for(int i = 0; i < suffixArray.size() - 1; i++) {
		for(int j = i+1; j < suffixArray.size(); j++) {
			int currentDistance = suffixArray.at(i).first - suffixArray.at(j).first;
			if(suffixArray.at(i).second <= ((arraySize / 2) - 1) && suffixArray.at(j).second >= (arraySize / 2)) { //If the first number is from the first array and second number from the second array
				if(abs(currentDistance) < abs(bestDistance) || abs(currentDistance) == 0) {
					bestDistance = currentDistance;
					int iLocation = low;
					int jLocation = high;
					break;
				}
			}
			else if(suffixArray.at(i).second >= (arraySize / 2) && suffixArray.at(j).second <= ((arraySize / 2) - 1)) { //If the first number is from the second array and second number from the first array
				if(abs(currentDistance) < abs(bestDistance) || abs(currentDistance) == 0) {
					bestDistance = currentDistance;
					int iLocation = low;
					int jLocation = high;
					break;
				}
			}
		}
	}
	return bestDistance;	
}

int thirdAlgorithm(std::vector<int> vector, int low, int high, std::string callType) {
	if(abs(high - low) < 1) {
		if(abs(vector.at(low)) < abs(bestSum) || vector.at(low) == 0) {
			bestSum = vector.at(low);
			int iLocation = low;
			int jLocation = low;
		}
		return vector.at(low);
	}
	else {
		int middle = floor((low + high) / 2.0);
		int left = thirdAlgorithm(vector, low, middle, "left");
		int right = thirdAlgorithm(vector, middle + 1, high, "right");
		int center = firstSumAlgorithm(vector, low, middle, high);
	}
	return bestSum;
}

int fourthAlgorithm(std::vector<int> vector, int low, int high, std::string callType) {
	if(abs(high - low) < 1) {
		if(abs(vector.at(low)) < abs(bestSum) || vector.at(low) == 0) {
			bestSum = vector.at(low);
			int iLocation = low;
			int jLocation = high;
		}
		return vector.at(low);
	}
	else {
		int middle = floor((low + high) / 2.0);
		int left = thirdAlgorithm(vector, low, middle, "left");
		int right = thirdAlgorithm(vector, middle + 1, high, "right");
		int center = secondSumAlgorithm(vector, low, middle, high);
	}
	return bestSum;
}

int main(int argc, char* argv[]) {
	std::vector<int> theVector;

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
		while(std::getline(input, number, ',')) {
			std::istringstream iss(number);
			int i;
			iss >> i;
			theVector.push_back(i); //Place it into the vector
		}

		std::ofstream ofs;
		std::string fileName = "output.txt";
		ofs.open(fileName.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app);
		std::cout << "[";
		ofs << "[";
		for(int i = 0; i < theVector.size(); i++) {
			if(i == theVector.size() - 1) {
				std::cout << theVector.at(i);
				ofs << theVector.at(i);
			}
			else {
				std::cout << theVector.at(i) << ",";
				ofs << theVector.at(i) << ",";
			}
		}
		std::cout << "],[";
		ofs << "],[";
		int sum = thirdAlgorithm(theVector, 0, theVector.size() - 1, "initial");
		//int sum = fourthAlgorithm(theVector, 0, theVector.size() - 1, "initial");
		for(int i = iLocation; i <= jLocation; i++) {
			if(i == jLocation) {
				std::cout << theVector.at(i);
				ofs << theVector.at(i);
			}	
			else {
				std::cout << theVector.at(i) << ",";
				ofs << theVector.at(i) << ",";
			}
		}
		std::cout << "]," << sum << std::endl;
		ofs << "]," << sum << std::endl;
		bestSum = 10000;
		bestDistance = 10000;
		theVector.clear();
	}
	//End File Input
	return 0;
}
