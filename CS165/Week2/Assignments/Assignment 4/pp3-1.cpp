/**********
** Program: pp3-1.cpp
** Author: Aryan Aziz
** Description: Based on user input values of gas consumed and miles traveled, outputs the miles per gallon
** Input: litersConsumed(double), milesTraveled(double) 
** Output: Users MPG
**********/

#include <iostream>

double litersConsumed;
double milesTraveled;
const double litersPerGallon = 0.264179; //Global Constant
double gallons;
double mpg;
char again;

double milesPerGallon(double litersConsumed, double milesTraveled){ //MPG Function
	gallons = litersConsumed * litersPerGallon; //Find the number of gallons
	mpg = milesTraveled / gallons; //Find the MPG
	return mpg;
}

int main() {
	do{
		std::cout << "Please enter the amount of gas, in liters, consumed: ";
		std::cin >> litersConsumed;

		std::cout << "Please enter the distance traveled, in miles: ";
		std::cin >> milesTraveled;

		std::cout << "For this trip, you had " << milesPerGallon(litersConsumed, milesTraveled) << "MPG." << std::endl;

		std::cout << "Calculate another trip? (y/n) ";
		std::cin >> again;
	} while (again == 'y' || again == 'Y');

	return 0;
}