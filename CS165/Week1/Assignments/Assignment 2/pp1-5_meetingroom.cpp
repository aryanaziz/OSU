/**********
** Program: pp1-5_meetingroom.cpp
** Author: Aryan Aziz
** Description: Reads the room capacity and number of people attending a particular meeting and determines whether the meeting abides by fire laws.
** Input: roomCap(int), attending(int)
** Output: Meeting legality 
**********/

#include <iostream>

int roomCap;
int attending; 
int spaceRemaining;
int extraPeople;

int main() {
	std::cout << "Please enter the meeting room capacity: ";
	std::cin >> roomCap;
	std::cout << "Please enter the number of people attending the meeting: ";
	std::cin >> attending;

	if (attending < roomCap) {
		spaceRemaining = roomCap - attending;
		std::cout << "Great! Your meeting follows fire regulation laws! You could even invite " << spaceRemaining << " more people!\n";
	}

	else if (attending == roomCap) {
		std::cout << "Perfect! Not only is your meeting following fire regulations, but you invited the maximum amount of people!\n";
	}

	else {
		extraPeople = attending - roomCap;
		std::cout << "Sorry, unfortunately your meeting breaks fire safety laws and as such you must shamefully tell " << extraPeople << " people that you don't like them and that they may not join the meeting.\n";
	}

	return 0;
}