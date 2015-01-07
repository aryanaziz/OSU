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
int numCandyBars;
int numGumBalls;

int main() {
	std::cout << "Please enter the number of tickets you have: ";
	std::cin >> totalTickets;

	numCandyBars = totalTickets / 10;
	numGumBalls = (totalTickets % 10) / 3;
	remainingTickets = totalTickets - ((numCandyBars * 10) + (numGumBalls * 3));

	std::cout << "With " << totalTickets << " tickets you can get:\n" << numCandyBars << " Candy Bars\n" << numGumBalls << " Gum Balls\nRemaining Tickets: " << remainingTickets << "\n";

	return 0;
}