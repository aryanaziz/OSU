/**********
** Program: A13E2.cpp
** Author: Aryan Aziz
** Description: Get the median, first quartile, and third quartile of a set of numbers. 
** Input: ifs(input.txt)
** Output: the median, first quartile, and third quartile
**********/

#include <iostream>
#include <fstream>
#include <vector>

bool isEven;
std::vector<int> values;
int input;

void calculateFirstQuartile(void) {
	double firstQuartile;
	if(isEven == true) {
		firstQuartile = (values[values.size() * .25] + values[(values.size() * .25) - 1]) / 2.0;
	}
	else {
		firstQuartile = values[values.size() * 1/4];
	}
	std::cout << "First Quartile: " << firstQuartile << std::endl;
}

void calculateMedian(void) {
	double median;
	if(isEven == true) {
		median = (values[values.size() * .5] + values[(values.size() * .5) - 1]) / 2.0;
	}
	else {
		median = values[values.size() * 1/2];
	}
	std::cout << "Median: " << median << std::endl;
}

void calculateThirdQuartile(void) {
	double thirdQuartile;
	if(isEven == true) {
		thirdQuartile = (values[values.size() * .75] + values[(values.size() * .75) - 1]) / 2.0;
	}
	else {
		thirdQuartile = values[values.size() * 3/4];
	}
	std::cout << "Third Quartile: " << thirdQuartile << std::endl;
}



int main() {

	std::ifstream ifs("input.txt");

	while(!ifs.eof()) {
		ifs >> input;
		values.push_back(input);
	}

	if(values.size() % 2 == 0) {
		isEven = true;
	}

	calculateFirstQuartile();
	calculateMedian();
	calculateThirdQuartile();

	return 0;
}