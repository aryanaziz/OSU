/**********
** Program: pp1-9_gumballs_division.cpp
** Author: Aryan Aziz
** Description: Reads the total amount of tickets from the user and displays the number of candy bars and gumballs they can receive.
** Input: totalTickets(int)
** Output: Number of gumballs and candy bars
**********/

#include <iostream>

int totalTickets;
int remainingTickets;
int numCandyBars = 0;
int numGumBalls = 0;

int main() {
	std::cout << "Please enter the number of tickets you have: ";
	std::cin >> totalTickets;

	remainingTickets = totalTickets;

	while((remainingTickets / 10) > 0){
		remainingTickets = remainingTickets - 10;
		numCandyBars++;
	}

	while((remainingTickets / 3) > 0){
		remainingTickets = remainingTickets - 3;
		numGumBalls++;
	}

	remainingTickets = totalTickets - ((numCandyBars * 10) + (numGumBalls * 3));

	std::cout << "With " << totalTickets << " tickets you can get:\n" << numCandyBars << " Candy Bars\n" << numGumBalls << " Gum Balls\nRemaining Tickets: " << remainingTickets << "\n";

	return 0;
}