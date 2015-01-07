/**********
** Program: A13E2.cpp
** Author: Aryan Aziz
** Description: 
** Input: 
** Output: 
**********/

#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> values;
int input;
double median;
double firstQuartile;
double thirdQuartile;
int medianPosition;
int firstQuartilePosition;
int firstQuartileLength;

double calculateMedian(void) {
	int medianLength = values.size();
	medianPosition = values.size();
	medianPosition = medianPosition / 2;
	//std::cout << "medianPosition: " << medianPosition << std::endl;
	//std::cout << "medianLength: " << medianLength << std::endl;
	if(medianLength % 2 != 0) {
		median = values[medianPosition];
		return median;
	}

	else {
		//std::cout << "Position 1: " << values[position] << std::endl;
		//std::cout << "Position 1: " << values[position - 1] << std::endl;
		median = (values[medianPosition] + values[medianPosition - 1]) / 2.0;
		return median;
	}
}

double calculateFirstQuartile(void) {
	firstQuartileLength = values.size();
	firstQuartilePosition = values.size();
	firstQuartilePosition = firstQuartilePosition / 4;
	if((firstQuartileLength % 2) != 0) {
		firstQuartile = values[firstQuartilePosition];
		return firstQuartile;
	}

	else {
		firstQuartile = (values[firstQuartilePosition] + values[firstQuartilePosition - 1] / 2.0);
		return firstQuartile;
	}
}

/*double calculateThirdQuartile(void) {
	if((firstQuartileLength % 2) != 0) {
		int thirdQuartilePosition = firstQuartilePosition + medianPosition;
		std::cout << "Third Quartile Position: " << thirdQuartilePosition << std::endl;
		std::cout << "Third Quartile Value: " << values[thirdQuartile] << std::endl;
		thirdQuartile = values[thirdQuartile];
		return thirdQuartile;
	}
}*/


int main() {
	std::ifstream ifs("input.txt");

	while(!ifs.eof()) {
		ifs >> input;
		values.push_back(input);
	}


	std::cout << "Median: " << calculateMedian() << std::endl;
	std::cout << "First Quartile: " << calculateFirstQuartile() << std::endl;
	//std::cout << "Third Quartile: " << calculateThirdQuartile() << std::endl;
	std::cout << values[4];


	return 0;
}