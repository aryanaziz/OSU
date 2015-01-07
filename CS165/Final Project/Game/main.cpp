/**********
** Program: A15E1.cpp
** Author: Aryan Aziz
** Description: 
** Input: 
** Output: 
**********/

//TODO
//1. BREAK OUT THE WHOLE THING INTO SUBFILES
//2. ADD NAME INPUT FOR NORMAL GAME
//2a. MAKE A CHECK FOR NAME INPUT/COMMAND LINE VALUE
//3. ADD OPTION TO VIEW HIGH SCORES



#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <vector>
#include <fstream>

bool finish = false;
std::string choices[4];
int boardArrayX = 4;
int boardArrayY = 3;
char** boardArray;
std::string name;

class InputSource {
	public:
		virtual char getCommand() = 0;
};

class CinInputSource : public InputSource {
	public:
		virtual char getCommand() {
			char move;
			std::cin >> move;
			return move;
		}
};

InputSource* daInputSource;

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
		node();
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

struct game {
	std::string name;
	int score;
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
	std::cout << "Or, if you're lost, enter 'b' for the room path back to the start" << std::endl;
	std::cout << "Conversely, you can also enter 'l' for a general board layout (no connections are shown because this is a maze!" << std::endl;
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
		while(move != 'n' && move != 's' && move != 'e' && move != 'w' && move != 'b' && move != 'l') {
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
		while(move == 'l') {
			std::cout << "The node layout of the board is: " << std::endl;
			for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					std::cout << boardArray[i][j] << " ";
				}
				std::cout << std::endl;
			}
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

void writeHighScore(game& x) {
	std::ofstream ofs;
	std::string fileName = "scores.txt";
	ofs.open(fileName.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app);
	ofs << x.name << " " << x.score;
}

void showHighScores(void) {
	std::ifstream ifs;
	std::string fileName = "scores.txt";
	ifs.open(fileName.c_str());

	std::string line;

	while(!ifs.eof()) {
		getline(ifs, line);
		std::cout << line;
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
		game newHighScore;
		newHighScore.name = name;
		newHighScore.score = roomList.size();
		for(int i = 0; i < roomList.size(); i++) {
			std::cout << roomList[i].getRoomId() << " ";
		}
		std::cout << std::endl;
		writeHighScore(newHighScore);
		finish = true;
	}
	else {
		//movementChoices(*x);
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



void generateBoard(int x, int y, node& z) {
    boardArray[x][y] = z.getRoomId();
}

void getName(char* x) {
	name = std::string(x);
}



int main(int argc, char** argv) {

	boardArray = new char*[boardArrayX];
	for(int i = 0; i < boardArrayX; ++i) {
    	boardArray[i] = new char[boardArrayY];
    }

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

	generateBoard(0, 0, a);
	generateBoard(0, 1, b);
	generateBoard(0, 2, c);
	generateBoard(0, 3, d);
	generateBoard(1, 0, e);
	generateBoard(1, 1, f);
	generateBoard(1, 2, g);
	generateBoard(1, 3, h);
	generateBoard(2, 0, i);
	generateBoard(2, 1, j);
	generateBoard(2, 2, k);
	generateBoard(2, 3, l);

	getName(argv[1]);
	showHighScores();

	while(finish == false) {
		makeMove(&a);
	}

	return 0;
}