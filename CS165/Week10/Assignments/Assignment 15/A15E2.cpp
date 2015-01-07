/**********
** Program: A15E2.cpp
** Author: Aryan Aziz
** Description: MazeGame+!
** Input: Various
** Output: Various
**********/

#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <vector>

bool finish = false;
std::string choices[4];

class node {
	private:
		bool northNeighbor;
		bool southNeighbor;
		bool eastNeighbor;
		bool westNeighbor;
		node *north;
		node *south;
		node *east;
		node *west;
		char roomId;
	public:
		//Constructor
		node(char x) {
			roomId = x;
		}
		//Setting the roomId
		void setRoomId(char x) {
			roomId = x;
		}
		//Getting the roomId
		char getRoomId(void) {
			return roomId;
		}
		//Setting the Bool Values
		void setNorthBool(bool x) {
			northNeighbor = x;
		}
		void setSouthBool(bool x) {
			southNeighbor = x;
		}
		void setEastBool(bool x) {
			eastNeighbor = x;
		}
		void setWestBool(bool x) {
			westNeighbor = x;
		}
		//Getting the Bool Values
		bool getNorthBool() {
			return northNeighbor;
		}
		bool getSouthBool() {
			return southNeighbor;
		}
		bool getEastBool() {
			return eastNeighbor;
		}
		bool getWestBool() {
			return westNeighbor;
		}
		//Setting the Neighbor Values
		void setNorth(node *x) {
			north = x;
		}
		void setSouth(node *x) {
			south = x;
		}
		void setEast(node *x) {
			east = x;
		}
		void setWest(node *x) {
			west = x;
		}
		//Setting the Neighbor Values
		node* getNorth() {
			return north;
		}
		node* getSouth() {
			return south;
		}
		node* getEast() {
			return east;
		}
		node* getWest() {
			return west;
		}
};

std::vector<node> roomList;
std::vector<node> breadCrumbs;

void initializeMaze(node *x, bool north, bool south, bool east, bool west) {
	x->setNorthBool(north);
	x->setSouthBool(south);
	x->setEastBool(east);
	x->setWestBool(west);
}

void initializeNeighbors(node *x, node *north, node *south, node *east, node *west) {
	x->setNorth(north);
	x->setSouth(south);
	x->setEast(east);
	x->setWest(west);
}

char getMove(node x) {
	std::string choices[4] = {"", "", "", ""};
	if(x.getNorthBool() == true) {
		choices[0] = "North";
	}
	if(x.getSouthBool() == true) {
		choices[1] = "South";
	}
	if(x.getEastBool() == true) {
		choices[2] = "East";
	}
	if(x.getWestBool() == true) {
		choices[3] = "West";
	}

	std::cout << "From here, you can go: ";
	for(int i = 0; i < 4; i++) {
		std::cout << choices[i] << " ";
	}
	std::cout << std::endl;
	bool validChoice = false;
	char move;
	std::cout << "Please enter your move (either N, S, E, W): " << std::endl;
	std::cout << "Or, if you're lost, enter 'b' for the room path back to the start";
	std::cin >> move;
	move = tolower(move);
	/*while(move != 'n' && move != 's' && move != 'e' && move != 'w') {
		std::cout << "That was not a valid move, please enter a valid move: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> move;
	}*/
	while(validChoice == false) {
		while(choices[0] != "North" && move == 'n') {
				std::cout << "That was not a valid move, please enter a valid move: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> move;
		}
		while(choices[1] != "South" && move == 's') {
				std::cout << "That was not a valid move, please enter a valid move: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> move;
		}
		while(choices[2] != "East" && move == 'e') {
				std::cout << "That was not a valid move, please enter a valid move: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> move;
		}
		while(choices[3] != "West" && move == 'w') {
				std::cout << "That was not a valid move, please enter a valid move: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> move;
		}
		while(move != 'n' && move != 's' && move != 'e' && move != 'w' && move != 'b') {
			std::cout << "That was not a valid move, please enter a valid move: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> move;
		}
		while(move == 'b') {
			std::cout << "The path back to the start is: ";
			for(int i = 0; i < breadCrumbs.size(); i++) {
				std::cout << breadCrumbs[i].getRoomId() << " ";
			}
			std::cout << std::endl;
			std::cout << "Please enter your move (either N, S, E, W): ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> move;
		}
		validChoice = true;
	}
	return move;
}

node* goThere(node *x, char y) {
	if(y == 'n') {
		return x->getNorth();
	}
	if(y == 's') {
		return x->getSouth();
	}
	if(y == 'e') {
		return x->getEast();
	}
	else {
		return x->getWest();
	}
}

void makeMove(node *x) {
	if(breadCrumbs.size() < 1) {
		breadCrumbs.push_back(*x);
	}
	std::cout << "================================" << std::endl;
	std::cout << "You're currently in room " << x->getRoomId() << std::endl;
	if(x->getRoomId() == 'l') {
		std::cout << "You've reached the end!" << std::endl;
		std::cout << "The route you took to get here: ";
		for(int i = 0; i < roomList.size(); i++) {
			std::cout << roomList[i].getRoomId() << " ";
		}
		std::cout << std::endl;
		finish = true;
	}
	else {
		roomList.push_back(*x);
		//
		if(breadCrumbs[breadCrumbs.size() - 2].getRoomId() != x->getRoomId() && breadCrumbs[breadCrumbs.size() - 1].getRoomId() != x->getRoomId()) {
			breadCrumbs.push_back(*x);
		}
		if(breadCrumbs[breadCrumbs.size() - 2].getRoomId() == x->getRoomId()) {
			breadCrumbs.pop_back();
		}
		makeMove(goThere(x, getMove(*x)));
	}
}

int main() {

	node a('a');
	node b('b');
	node c('c');
	node d('d');
	node e('e');
	node f('f');
	node g('g');
	node h('h');
	node i('i');
	node j('j');
	node k('k');
	node l('l');
	//Setup A
	initializeMaze(&a, false, true, true, false);
	initializeNeighbors(&a, NULL, &e, &b, NULL);
	//Setup B
	initializeMaze(&b, false, true, false, true);
	initializeNeighbors(&b, NULL, &f, NULL, &a);
	//Setup C
	initializeMaze(&c, false, true, true, false);
	initializeNeighbors(&c, NULL, &g, &d, NULL);
	//Setup D
	initializeMaze(&d, false, false, false, true);
	initializeNeighbors(&d, NULL, NULL, NULL, &c);
	//Setup E
	initializeMaze(&e, true, true, false, false);
	initializeNeighbors(&e, &a, &i, NULL, NULL);
	//Setup F
	initializeMaze(&f, true, false, true, false);
	initializeNeighbors(&f, &b, NULL, &g, NULL);
	//Setup G
	initializeMaze(&g, true, true, true, true);
	initializeNeighbors(&g, &c, &k, &h, &f);
	//Setup H
	initializeMaze(&h, false, true, false, true);
	initializeNeighbors(&h, NULL, &l, NULL, &g);
	//Setup I
	initializeMaze(&i, true, false, true, false);
	initializeNeighbors(&i, &e, NULL, &j, NULL);
	//Setup J
	initializeMaze(&j, false, false, false, true);
	initializeNeighbors(&j, NULL, NULL, NULL, &i);
	//Setup K
	initializeMaze(&k, true, false, false, false);
	initializeNeighbors(&k, &g, NULL, NULL, NULL);
	//Setup L
	initializeMaze(&l, true, false, false, false);
	initializeNeighbors(&l, &h, NULL, NULL, NULL);

	while(finish == false) {
		makeMove(&a);
	}

	return 0;
}