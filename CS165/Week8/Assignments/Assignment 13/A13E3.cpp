/**********
** Program: A13E3.cpp
** Author: Aryan Aziz
** Description: Grabs the information from 2 files and sorts the numbers and outputs them into a 3rd file. 
** Input: inputFile1, inputFile2
** Output: outputFile1. (The full sorted list).
**********/

#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> inputValues1;
std::vector<int> inputValues2;
std::vector<int> outputValues;
int input;

void sort(std::ifstream &inputFile1, std::ifstream &inputFile2, std::ofstream &outputFile) {

	while(!inputFile1.eof()) {
		inputFile1 >> input;
		inputValues1.push_back(input);
	}

	while(!inputFile2.eof()) {
		inputFile2 >> input;
		inputValues2.push_back(input);
	}

	int inputFile1Length = inputValues1.size();
	int inputFile2Length = inputValues2.size();
	int i = 0;
	int j = 0;

	while(i < inputFile1Length && j < inputFile2Length) {
		if(inputValues1[i] <= inputValues2[j]) {
			outputValues.push_back(inputValues1[i]);
			i++;
		}
		else {
			outputValues.push_back(inputValues2[j]);
			j++;
		}
	}
	if(i < inputFile1Length) {
		for(int k = i; k < inputFile1Length; k++) {
			outputValues.push_back(inputValues1[k]);
		}
	}
	else {
		for(int m = j; j < inputFile2Length; j++) {
			outputValues.push_back(inputValues2[j]);
		}
	}

	for(int i = 0; i < outputValues.size(); i++) {
		outputFile << outputValues[i] << std::endl;
		std::cout << outputValues[i] << std::endl;
	}
}

int main() {

	std::ifstream inputFile1("input.txt");
	std::ifstream inputFile2("input2.txt");
	std::ofstream outputFile("output.txt");

	sort(inputFile1, inputFile2, outputFile);

	return 0;
}