/**********
** Program: A13P1.cpp
** Author: Aryan Aziz
** Description: 
** Input: 
** Output: 
**********/

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

int board[22][80];
int tempBoard[22][80];
char again;
std::string coordinate;
std::string coordinateNumberString;
int coordinateNumber;
bool validInput;
int numGenerations;
std::string numGenerationsString;
bool numGenerationsValid;

void generateBoard(void) {
	//Fill the Board with empty values to start
	for(int i = 0; i < 22; i++) {
		for(int j = 0; j < 80; j++) {
			board[i][j] = 0;
		}
	}





	//Begin the big board initialization
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

void displayBoard(void) {
	for(int i = 0; i < 22; i++) {
		std::cout << std::endl;
		for(int j = 0; j < 80; j++) {
			if(board[i][j] == 0) {
				std::cout << " ";
			}
			if(board[i][j] == 1) {
				std::cout << "*";
			}
		}
	}
	std::cout << std::endl;
}

void copyArray(int array1[22][80], int array2[22][80]) {
	for(int i = 0; i < 22; i++) {
		for(int j = 0; j < 80; j++) {
			array2[i][j] = array1[i][j];
		}
	}
}

void runGeneration(int x) {
	int generationsRan = 0;
	while(generationsRan < x) {
		copyArray(board, tempBoard); //put the board into a temporary array so any changes we make won't effect the other cells that haven't been processed yet. 
		for(int i = 1; i < 21; i++) { //Main Board
			for(int j = 1; j < 79; j++) {
				int neighbors = 0;
				neighbors = board[i][j+1] + board[i][j-1] + board[i-1][j] + board[i-1][j-1] + board[i-1][j+1] + board[i+1][j] + board[i+1][j-1] + board[i+1][j+1];

				if(neighbors < 2 || neighbors > 3) {
					tempBoard[i][j] = 0;
					//std::cout << "Board[" << i << "][" << j << "] Cell Dying" << std::endl;
				}

				if(neighbors == 2) {
					tempBoard[i][j] = board[i][j];
					//std::cout << "Board[" << i << "][" << j << "] Cell Stays Stagnant" << std::endl;
				}

				if(neighbors == 3) {
					tempBoard[i][j] = 1;
					//std::cout << "Board[" << i << "][" << j << "] Cell Birth" << std::endl;
				}
			}
		}
		for(int j = 0; j < 79; j++) { //Top Row
			int neighbors = 0;
			neighbors = board[0][j+1] + board[0][j-1] + board[21][j+1] + board[21][j-1] + board[21][j] + board[1][j+1] + board[1][j-1] + board[1][j];

				if(neighbors < 2 || neighbors > 3) {
					tempBoard[0][j] = 0;
					//std::cout << "Board[" << i << "][" << j << "] Cell Dying" << std::endl;
				}

				if(neighbors == 2) {
					tempBoard[0][j] = board[0][j];
					//std::cout << "Board[" << i << "][" << j << "] Cell Stays Stagnant" << std::endl;
				}

				if(neighbors == 3) {
					tempBoard[0][j] = 1;
					//std::cout << "Board[" << i << "][" << j << "] Cell Birth" << std::endl;
				}
		}
		for(int j = 0; j < 79; j++) { //Bottom Row
			int neighbors = 0;
			neighbors = board[21][j+1] + board[21][j-1] + board[0][j+1] + board[0][j-1] + board[0][j] + board[20][j+1] + board[20][j-1] + board[20][j];

				if(neighbors < 2 || neighbors > 3) {
					tempBoard[21][j] = 0;
					//std::cout << "Board[" << i << "][" << j << "] Cell Dying" << std::endl;
				}

				if(neighbors == 2) {
					tempBoard[21][j] = board[0][j];
					//std::cout << "Board[" << i << "][" << j << "] Cell Stays Stagnant" << std::endl;
				}

				if(neighbors == 3) {
					tempBoard[21][j] = 1;
					//std::cout << "Board[" << i << "][" << j << "] Cell Birth" << std::endl;
				}
		}
		for(int i = 0; i < 22; i++) { //Left Column
			int neighbors = 0;
			neighbors = board[i+1][0] + board[i-1][0] + board[i+1][1] + board[i-1][1] + board[i][1] + board[i+1][79] + board[i-1][79] + board[i][79];

				if(neighbors < 2 || neighbors > 3) {
					tempBoard[i][0] = 0;
					//std::cout << "Board[" << i << "][" << j << "] Cell Dying" << std::endl;
				}

				if(neighbors == 2) {
					tempBoard[i][0] = board[i][0];
					//std::cout << "Board[" << i << "][" << j << "] Cell Stays Stagnant" << std::endl;
				}

				if(neighbors == 3) {
					tempBoard[i][0] = 1;
					//std::cout << "Board[" << i << "][" << j << "] Cell Birth" << std::endl;
				}
		}
		for(int i = 0; i < 22; i++) { //Right Column
			int neighbors = 0;
			neighbors = board[i+1][21] + board[i-1][21] + board[i+1][20] + board[i-1][20] + board[i][20] + board[i+1][0] + board[i-1][0] + board[i][0];

				if(neighbors < 2 || neighbors > 3) {
					tempBoard[i][21] = 0;
					//std::cout << "Board[" << i << "][" << j << "] Cell Dying" << std::endl;
				}

				if(neighbors == 2) {
					tempBoard[i][21] = board[i][21];
					//std::cout << "Board[" << i << "][" << j << "] Cell Stays Stagnant" << std::endl;
				}

				if(neighbors == 3) {
					tempBoard[i][21] = 1;
					//std::cout << "Board[" << i << "][" << j << "] Cell Birth" << std::endl;
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
	for(int i = 0; i < 22; i++) {
		for(int j = 0; j < 80; j++) {
			board[i][j] = 1;
		}
	}


	displayBoard();

	std::cout << "Please enter the number of generations you would like to run: ";
	std::cin >> numGenerations;


	runGeneration(numGenerations);

	return 0;
}