/**********
** Program: pp3-5.cpp
** Author: Aryan Aziz
** Description: Takes in a user's information and outputs their various clothing sizes.
** Input: height(double), weight(double), age(int)
** Output: Clothing sizes
**********/

#include <iostream>

double height;
double weight;
int age;
int extraInches;
double hatSize;
double jacketSize;
double waistSize;
char again;

double getHatSize(double height, double weight){ //Hat Size Function
	hatSize = (weight / height) * 2.9;
	return hatSize;
}

double getJacketSize(double height, double weight, int age){ //Jacket Size Function
	if(age <= 30){ //If they are 30 or younger
		jacketSize = (height * weight) / 288; //Calculate jacket size
	}
	if(age > 30){ //If they are over 30
		extraInches = (age - 30) / 10; //Find out how many extra 1/8ths need to be added.
		jacketSize = ((height * weight) / 288 ) + ((1.0/8.0) * extraInches); //Calculate jacket size with the extra inches
	}
	return jacketSize;
}

double getWaistSize(double weight, double age){ //Waist Size Function
	if(age <= 28){ //If they are 28 or younger
		waistSize = weight / 5.7; //Calculate waist size
	}
	if(age > 28){ //If they are older than 28
		extraInches = (age - 28) / 2; //Find out how many extra 1/10ths they need
		waistSize = (weight / 5.7) + ((1.0/10.0) * extraInches); //Calculate waist size with the extra inches
	}
	return waistSize;
}



int main(){
	do {
		std::cout << "Please enter your height in inches: ";
		std::cin >> height;
		std::cout << "Please enter your weight in pounds: ";
		std::cin >> weight;
		std::cout << "Please enter your age in years: ";
		std::cin >> age;

		std::cout << "HatSize: " << getHatSize(height, weight) << std::endl;
		std::cout << "JacketSize: " << getJacketSize(height, weight, age) << std::endl;
		std:: cout << "WaistSize: " << getWaistSize(weight, age) << std::endl;

		std::cout << "Calculate another person? (y/n) ";
		std::cin >> again;
	} while (again == 'y' || again == 'Y');


	return 0;
}