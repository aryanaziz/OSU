/**********
** Program: A12E4.cpp
** Author: Aryan Aziz
** Description: Program that determines what position you should be to be the winning suitor. 
** Input: none
** Output: none
**********/

#include <iostream>
#include <vector>

std::vector<int> suitors;

void createVector(int x) {
	for(int i = 1; i <= x; i++) {
		suitors.push_back(i);
	}
}

int eliminateSuitors(void) {
	int currentIndex = 0;
	int counter = 1;

	while(suitors.size() > 1) {
		int endIndex = suitors.size() - 1;
		if(currentIndex > endIndex) {
			currentIndex = 0;
		}
		if(counter % 3 == 0) {
			//std::cout << "Current Counter Var: " << counter;
			suitors.erase(suitors.begin() + currentIndex);
			for(int i = 0; i < suitors.size(); i++) {
				//std::cout << suitors[i] << " ";
			}
			//std::cout << std::endl;
			counter = 1;
		}
		else {
			currentIndex++;
			counter++;
		}	
	}

	return suitors[0];
}


int main() {

	createVector(12);
	/*for(int i = 0; i < suitors.size(); i++) {
		std::cout << suitors[i] << " ";
	}
	std::cout << std::endl;*/

	std::cout << "If you want her hand, you better be the " << eliminateSuitors() << " person in line" << std::endl;
	
	

	return 0;
}