/**********
** Program: Final Project
** Author: Aryan Aziz
** Description: Maze game with some extra features!
** Input: Various
** Output: Various
**********/

/**********
** Re-Evaluation Sections
** Not sure if the items I want re-evaluated can be, but if it's possible please look into the following:
** Week 4 Assignment; Testing Section
**		In the program, I lost 5 points for "Treats uppercase and lowercase characters as different values"
**		Please see line 109 where I convert all values to lowercase so that they can be treated as the same. 
** Week 6 Assignment; Implementation
**		In the assignment, I lost 2 points for "Not playing again should probably return to the main menu."
**		On line 366, I have the end of the do-while loop that takes the user back to the main menu if they want to play again
**********/

#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <vector> //######## Requirement #32 ########
#include <fstream>
#include "node.h" //######## Requirement #26 ########
#include <cstdlib>

//Variables
bool finish = false;
std::string choices[4];
int boardArrayX = 4;
int boardArrayY = 3;
char** boardArray;
std::string name; //######## Requirement #15 ########
char nameArray[20];
char mainMenuChoice;
std::vector<node> roomList; //######## Requirement #28 ########
std::vector<node> breadCrumbs;
char again;

namespace aziza { //######## Requirement #25 ########
	void initializeMaze(node *x, bool north, bool south, bool east, bool west) {
		x->setNorthBool(north); //######## Requirement #24 ########
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

	void generateBoard(int x, int y, node& z) {
    	boardArray[x][y] = z.getRoomId();
	}

	void getName(char* x) {
		name = std::string(x);
	}
}

class InputSource { //######## Requirement #21 ########
	public:
		virtual char getCommand() = 0;
};

class CinInputSource : public InputSource { //######## Requiement #33 ########
	public:
		virtual char getCommand() { //######## Requiement #34 ########
			char move;
			std::cin >> move;
			return move;
		}
};

InputSource* daInputSource;

struct game { //######## Requirement #20 ########
	std::string name;
	int score;
};

//Gets the possible moves and gets the move from the user
char getMove(node x) { //######## Requirement #13 ########
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
	move = daInputSource->getCommand(); //Get the move
	move = tolower(move); //Lowercase it so that it you treat upper and lowercase the same

	while(validChoice == false) {
		while(choices[0] != "North" && move == 'n') { //If they enter n and they can't move north
				std::cout << "That was not a valid move, please enter a valid move: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				move = daInputSource->getCommand();
		}
		while(choices[1] != "South" && move == 's') { //If they enter s and they can't move south
				std::cout << "That was not a valid move, please enter a valid move: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				move = daInputSource->getCommand();
		}
		while(choices[2] != "East" && move == 'e') { //If they enter e and they can't move east
				std::cout << "That was not a valid move, please enter a valid move: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				move = daInputSource->getCommand();
		}
		while(choices[3] != "West" && move == 'w') { //If they enter w and they can't move west
				std::cout << "That was not a valid move, please enter a valid move: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				move = daInputSource->getCommand();
		}
		//If they enter anything else
		while(move != 'n' && move != 's' && move != 'e' && move != 'w' && move != 'b' && move != 'l') { //######## Requirement #9 ########
			std::cout << "That was not a valid move, please enter a valid move: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			move = daInputSource->getCommand();
		}
		while(move == 'b') { //If they enter the breadcrumb choice
			std::cout << "The path back to the start is: ";
			for(int i = 0; i < breadCrumbs.size(); i++) {
				std::cout << breadCrumbs[i].getRoomId() << " ";
			}
			std::cout << std::endl;
			std::cout << "Please enter your move (either N, S, E, W): ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			move = daInputSource->getCommand();
		}
		while(move == 'l') { //If they enter the layout
			std::cout << "The node layout of the board is: " << std::endl;
			for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					std::cout << boardArray[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "Please enter your move (either N, S, E, W): ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			move = daInputSource->getCommand();
		}
		validChoice = true;
	}
	return move;
}

node* goThere(node *x, char y) { //Actually gets the specific neighbor
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

void writeHighScore(game& x) { //######## Requirement #31 ########
	std::ofstream ofs;
	std::string fileName = "scores.txt";
	ofs.open(fileName.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app);
	ofs << x.name << " " << x.score << "\r\n";
}

void showHighScores(void) {
	std::ifstream ifs;
	std::string fileName = "scores.txt";
	ifs.open(fileName.c_str());

	std::string line;

	while(!ifs.eof()) {
		getline(ifs, line);
		std::cout << line << std::endl;
	}

	std::cout << std::endl;
}

//Main move making Function
void makeMove(node *x) { //######## Requirement #10 ########
	if(breadCrumbs.size() < 1) {
		breadCrumbs.push_back(*x); //Ads the initial value
	}
	std::cout << "================================" << std::endl;
	std::cout << "You're currently in room " << x->getRoomId() << std::endl;
	if(x->getRoomId() == 'l') { //If they reached the end
		std::cout << "You've reached the end!" << std::endl;
		std::cout << "The route you took to get here: ";
		game newHighScore;
		newHighScore.name = name;
		newHighScore.score = roomList.size();
		for(int i = 0; i < roomList.size(); i++) {
			std::cout << roomList[i].getRoomId() << " "; //Show their path
		}
		std::cout << std::endl;
		writeHighScore(newHighScore);
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
		makeMove(goThere(x, getMove(*x))); //######## Requirement #16 ########
	}
}

//Starts/runs the actual game itself
void runGame(node& a) {
	while(finish == false) { //######## Requiremeent #6 ########

		std::cout << "What would you like to do?" << std::endl;
		std::cout << "1. Play Game" << std::endl;
		std::cout << "2. View High Scores" << std::endl;
		std::cin >> mainMenuChoice;

		//Since validChoice is defined in another function it can also be used here independently
		bool validChoice = false; //######## Requirement #12 ########
		while(validChoice == false) { //######## Requirement #5 ########
			if(mainMenuChoice == '1') {
				makeMove(&a);
				validChoice = true;
			}
			else if(mainMenuChoice == '2') {
				showHighScores();
				validChoice = true;
				finish = true;
			}
			else {
				std::cout << "That was not a valid option, please enter 1 or 2: ";
			}
		}	
	}

	std::cout << "Return to the main menu? (y/n) "; //Ask if you want to play again.
    std::cin >> again;
    std::cin.ignore();
    std::cin.clear();
    finish = false;
}

int randomNumberGenerator(void) { //######## Requirement #7 ########
	int randomNum;
	srand(time(NULL));
	randomNum = rand() % 100 + 1; 
	return randomNum;
}


int main(int argc, char** argv) {

	//Setup the dynamic 2d array
	boardArray = new char*[boardArrayX]; //######## Requirement #18 ######## Requirement #22 ########
	for(int i = 0; i < boardArrayX; ++i) {
    	boardArray[i] = new char[boardArrayY]; //######## Requirement #17 ########
    }

    //Initialize all the nodes
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
	aziza::initializeMaze(&a, false, true, true, false); //######## Requirement #11 ########
	aziza::initializeNeighbors(&a, NULL, &e, &b, NULL);
	//Setup B
	aziza::initializeMaze(&b, false, true, false, true);
	aziza::initializeNeighbors(&b, NULL, &f, NULL, &a);
	//Setup C
	aziza::initializeMaze(&c, false, true, true, false);
	aziza::initializeNeighbors(&c, NULL, &g, &d, NULL);
	//Setup D
	aziza::initializeMaze(&d, false, false, false, true);
	aziza::initializeNeighbors(&d, NULL, NULL, NULL, &c);
	//Setup E
	aziza::initializeMaze(&e, true, true, false, false);
	aziza::initializeNeighbors(&e, &a, &i, NULL, NULL);
	//Setup F
	aziza::initializeMaze(&f, true, false, true, false);
	aziza::initializeNeighbors(&f, &b, NULL, &g, NULL);
	//Setup G
	aziza::initializeMaze(&g, true, true, true, true);
	aziza::initializeNeighbors(&g, &c, &k, &h, &f);
	//Setup H
	aziza::initializeMaze(&h, false, true, false, true);
	aziza::initializeNeighbors(&h, NULL, &l, NULL, &g);
	//Setup I
	aziza::initializeMaze(&i, true, false, true, false);
	aziza::initializeNeighbors(&i, &e, NULL, &j, NULL);
	//Setup J
	aziza::initializeMaze(&j, false, false, false, true);
	aziza::initializeNeighbors(&j, NULL, NULL, NULL, &i);
	//Setup K
	aziza::initializeMaze(&k, true, false, false, false);
	aziza::initializeNeighbors(&k, &g, NULL, NULL, NULL);
	//Setup L
	aziza::initializeMaze(&l, true, false, false, false);
	aziza::initializeNeighbors(&l, &h, NULL, NULL, NULL);

	//Setup the board layout for help
	aziza::generateBoard(0, 0, a);
	aziza::generateBoard(0, 1, b);
	aziza::generateBoard(0, 2, c);
	aziza::generateBoard(0, 3, d);
	aziza::generateBoard(1, 0, e);
	aziza::generateBoard(1, 1, f);
	aziza::generateBoard(1, 2, g);
	aziza::generateBoard(1, 3, h);
	aziza::generateBoard(2, 0, i);
	aziza::generateBoard(2, 1, j);
	aziza::generateBoard(2, 2, k);
	aziza::generateBoard(2, 3, l);

	daInputSource = new CinInputSource();


	//Main loop
	do{
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "  __  __           ____________    _____          __  __ ______ " << std::endl;
		std::cout << " |  \\/  |   /\\    |___  /  ____|  / ____|   /\\   |  \\/  |  ____|" << std::endl;
		std::cout << " | \\  / |  /  \\      / /| |__    | |  __   /  \\  | \\  / | |__   " << std::endl;
		std::cout << " | |\\/| | / /\\ \\    / / |  __|   | | |_ | / /\\ \\ | |\\/| |  __|  " << std::endl;
		std::cout << " | |  | |/ ____ \\  / /__| |____  | |__| |/ ____ \\| |  | | |____ " << std::endl;
		std::cout << " |_|  |_/_/    \\_\\/_____|______|  \\_____/_/    \\_\\_|  |_|______|" << std::endl;
		std::cout << "Welcome to the MazeGame!" << std::endl; //######## Requirement #1 ########
		if(argc <= 1) { //######## Requirement #4 ########
			std::cout << "What's your name? ";
			std::cin >> name; //######## Requirement #2 ########
		}
		else {
			aziza::getName(argv[1]); //######## Requirement #19 ########
		}
		runGame(a);
	} while (again == 'y' || again == 'Y');

	return 0;
}