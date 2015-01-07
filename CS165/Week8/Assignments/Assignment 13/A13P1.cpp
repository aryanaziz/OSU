/**********
** Program: A13P1.cpp
** Author: Aryan Aziz
** Description: Conway's game of life
** Input: boardType(int), again(char), coordinate(std::string), numGenerations(int)
** Output: Game of life info
**********/

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <algorithm>

int board[22][80];
int tempBoard[22][80];
int boardType;
bool validInput;
char again;
std::string coordinate;
std::string coordinateNumberString;
int coordinateNumber;
int numGenerations;

void displayBoard(void) {
	for(int y = 0; y < 22; y++) {
		std::cout << std::endl;
		for(int x = 0; x < 80; x++) {
			if(board[y][x] == 0) {
				std::cout << " ";
			}
			if(board[y][x] == 1) {
				std::cout << "*";
			}
		}
	}
	std::cout << std::endl;
}

void enterValues(void) {
	do {
		validInput = false; //Set it to false to start and only set to true if it's cool

		while (validInput == false) {
			std::cout << "Please enter a Letter(row) Number(column) coordinate (EX: A1 or B20) to place a living cell. Valid Range (A-V and 1-80): ";
			std::cin >> coordinate;

			if(coordinate.length() >= 2 && coordinate.length() <= 3){ //If it's LetterNum or LetterNumNum
				if(isalpha(coordinate[0])) { //If the first item is a letter
					if(isdigit(coordinate[1])) { //If the 2nd item is a number
						if(coordinate.length() == 2) { //When there are only 2 items (no other checks needed)
							coordinateNumberString = coordinate.substr(1, 1);
							coordinateNumber = atoi(coordinateNumberString.c_str()); //turn the string into an int
							validInput = true;
						}
						if(coordinate.length() == 3) { //When there is 3 items (LetterNumNum)
							if(isdigit(coordinate[2])) { //If the 2nd item is a digit
								coordinateNumberString = coordinate.substr(1, 2);
								coordinateNumber = atoi(coordinateNumberString.c_str()); //turn the string into an int
								if(coordinateNumber < 80 && coordinateNumber > 0) { //If the digit itself is valid
									validInput = true; //Finally set it to true and move on
								}
								else { //the number is too big or small
									validInput = false;
								}
								
							}
							else { //2nd item isn't a number
								validInput = false;
							}
						}
					}
					else { //the first number isn't a digit
						validInput = false;
					}
				}
				else { //the first item is not a letter
					validInput = false;
				}									
			}
			else { //the inpt is too big or too small
				validInput = false;
			}
		}



		//Once everything is ready to go. 
		std::transform(coordinate.begin(), coordinate.end(), coordinate.begin(), ::tolower); //convert the letter to lowercase

		switch (coordinate[0]) { //converting from letter to a row number
			case 'a':
				board[0][coordinateNumber - 1] = 1;
				break;
			case 'b':
				board[1][coordinateNumber - 1] = 1;
				break;
			case 'c':
				board[2][coordinateNumber - 1] = 1;
				break;
			case 'd':
				board[3][coordinateNumber - 1] = 1;
				break;
			case 'e':
				board[4][coordinateNumber - 1] = 1;
				break;
			case 'f':
				board[5][coordinateNumber - 1] = 1;
				break;
			case 'g':
				board[6][coordinateNumber - 1] = 1;
				break;
			case 'h':
				board[7][coordinateNumber - 1] = 1;
				break;
			case 'i':
				board[8][coordinateNumber - 1] = 1;
				break;
			case 'j':
				board[9][coordinateNumber - 1] = 1;
				break;
			case 'k':
				board[10][coordinateNumber - 1] = 1;
				break;
			case 'l':
				board[11][coordinateNumber - 1] = 1;
				break;
			case 'm':
				board[12][coordinateNumber - 1] = 1;
				break;
			case 'n':
				board[13][coordinateNumber - 1] = 1;
				break;
			case 'o':
				board[14][coordinateNumber - 1] = 1;
				break;
			case 'p':
				board[15][coordinateNumber - 1] = 1;
				break;
			case 'q':
				board[16][coordinateNumber - 1] = 1;
				break;
			case 'r':
				board[17][coordinateNumber - 1] = 1;
				break;
			case 's':
				board[18][coordinateNumber - 1] = 1;
				break;
			case 't':
				board[19][coordinateNumber - 1] = 1;
				break;
			case 'u':
				board[20][coordinateNumber - 1] = 1;
				break;
			case 'v':
				board[21][coordinateNumber - 1] = 1;
				break;
		}


		std::cout << "Place another living cell? (y/n) "; //Ask if you want to place another living cell again.
		std::cin >> again;
		std::cin.ignore();
		std::cin.clear();
	} while (again == 'y' || again == 'Y');
}

void generateBoard(void) {
	//Fill the Board with empty values to start
	for(int y = 0; y < 22; y++) {
		for(int x = 0; x < 80; x++) {
			board[y][x] = 0;
		}
	}

	std::cout << "Would you like to: " << std::endl << "1) Generate a random board" << std::endl << "2) Enter in values" << std::endl;
	std::cin >> boardType;

	if(boardType == 1) {
		srand(time(NULL));
		for(int y = 0;y < 22; y++) {
			for(int x = 0; x < 80; x++) {
				board[y][x] = rand() % 2;
			}
		}
	}
	else {
		enterValues();
	}
}

void copyArray(int array1[22][80], int array2[22][80]) {
	for(int y = 0; y < 22; y++) {
		for(int x = 0; x < 80; x++) {
			array2[y][x] = array1[y][x];
		}
	}
}

void runGeneration(int x) {
	int generationsRan = 0;
	while(generationsRan < x) {
		copyArray(board, tempBoard);
		//Do the main board (no edges)
		for(int y = 1; y < 21; y++) {
			for(int x = 1; x < 79; x++) {
				int neighbors = 0;
				neighbors = board[y][x+1] + board[y][x-1] + board[y-1][x] + board[y-1][x-1] + board[y-1][x+1] + board[y+1][x] + board[y+1][x-1] + board[y+1][x+1];

				if(neighbors < 2 || neighbors > 3) {
					tempBoard[y][x] = 0;
				}

				if(neighbors == 2) {
					tempBoard[y][x] = board[y][x];
				}

				if(neighbors == 3) {
					tempBoard[y][x] = 1;
				}
			}
		}

		//Do the top row
		for(int x = 1; x < 79; x++) {
			int neighbors = 0;
			neighbors = board[0][x+1] + board[0][x-1] + board[1][x] + board[1][x+1] + board[1][x-1] + board[21][x] + board[21][x+1] + board[21][x-1];
			if(neighbors < 2 || neighbors > 3) {
				tempBoard[0][x] = 0;
			}

			if(neighbors == 2) {
				tempBoard[0][x] = board[0][x];
			}

			if(neighbors == 3) {
				tempBoard[0][x] = 1;
			}
		}

		//Do the bottom row
		for(int x = 1; x < 79; x++) {
			int neighbors = 0;
			neighbors = board[21][x+1] + board[21][x-1] + board[20][x] + board[20][x+1] + board[20][x-1] + board[0][x] + board[0][x+1] + board[0][x-1];
			if(neighbors < 2 || neighbors > 3) {
				tempBoard[21][x] = 0;
			}

			if(neighbors == 2) {
				tempBoard[21][x] = board[0][x];
			}

			if(neighbors == 3) {
				tempBoard[21][x] = 1;
			}
		}

		//Do the left column
		for(int y = 1; y < 21; y++) {
			int neighbors = 0;
			neighbors = board[y+1][0] + board[y-1][0] + board[y][1] + board[y+1][1] + board[y-1][1] + board[y][79] + board[y+1][79] + board[y-1][79];

			if(neighbors < 2 || neighbors > 3) {
				tempBoard[y][0] = 0;
			}

			if(neighbors == 2) {
				tempBoard[y][0] = board[y][0];
			}

			if(neighbors == 3) {
				tempBoard[y][0] = 1;
			}
		}

		//Do the right column
		for(int y = 1; y < 21; y++) {
			int neighbors = 0;
			neighbors = board[y+1][79] + board[y-1][79] + board[y][78] + board[y+1][78] + board[y-1][78] + board[y][0] + board[y+1][0] + board[y-1][0];

			if(neighbors < 2 || neighbors > 3) {
				tempBoard[y][0] = 0;
			}

			if(neighbors == 2) {
				tempBoard[y][0] = board[y][0];
			}

			if(neighbors == 3) {
				tempBoard[y][0] = 1;
			}
		}

		copyArray(tempBoard, board); //Put the temporary board back into the original array
		generationsRan++;
		std::cout << "##### Generation: " << generationsRan << " #####" << std::endl;
		displayBoard();
	}
}

int main() {
	generateBoard();
	displayBoard();

	std::cout << "Please enter the number of generations you would like to run: ";
	std::cin >> numGenerations;
	while(!std::cin) {
		std::cout << "Please enter the number of generations you would like to run: ";
		std::cin.clear();
		std::cin.ignore();
		std::cin >> numGenerations;
	}

	runGeneration(numGenerations);

}
