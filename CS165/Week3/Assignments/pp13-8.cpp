/**********
** Program: pp13-8.cpp
** Author: Aryan Aziz
** Description: Calculates the amount of money you will have after compound interest in a certain amount of years. 
** Input: money(int), interest(double), years(int)
** Output: Total Money.  
**********/

#include <iostream>
#include <math.h>

double money;
double interest;
int years;

/*double compoundInterest(int money, double interest, int years){
	interest = interest/100;
	if(years == 1){
		return money * (1+interest);
	}
	else{
		return (1 + interest) * compoundInterest(money, interest, years - 1);
	}
}*/

double compoundInterest(int money, double interest, int years){
	if(years == 0){
		return money;
	}
	else {
		return (1 + interest) * compoundInterest(money, interest, years - 1);
	}
}	

int main(){
	std::cout << "Enter the amount of money you're starting with in dollars: ";
	std::cin >> money;
	std::cout << "Enter the interest rate (as a percentage): ";
	std::cin >> interest;
	std::cout << "Enter the number of years: ";
	std::cin >> years;

	interest = interest/100;
	
	std::cout << "Your total money after " << years << " years is: $" << compoundInterest(money, interest, years) << std::endl;
	return 0;
}