/**********
** Program: A7E4.cpp
** Author: Aryan Aziz
** Description: Tic Tac Toe style program. Program ends when all spaces have been used (does not determine a winner)
** Input: move(int)
** Output: Tic Tac Toe board. 
**********/

#include <iostream>
char *board;
int szUsedSpace[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
int move;
int totalMoves = 0;

void createBoard(void){ //Create the board
	board = new char[9];
	board[0] = '1'; 
	board[1] = '2';
	board[2] = '3';
	board[3] = '4';
	board[4] = '5';
	board[5] = '6'; 
	board[6] = '7';
	board[7] = '8';
	board[8] = '9';
}

void displayBoard(void){ //Display the current board
	std::cout << board[0] << "   " << board[1] << "   " << board[2] << std::endl;
	std::cout << board[3] << "   " << board[4] << "   " << board[5] << std::endl;
	std::cout << board[6] << "   " << board[7] << "   " << board[8] << std::endl;
}

int main() {
	createBoard();
	displayBoard();

	while(totalMoves < 9){ //End before the max moves
		if(totalMoves % 2 == 0){ //If it's the first player's turn
			std::cout << "[PLAYER 1] Please enter a position: ";
			std::cin >> move;
			while(std::cin.fail()){ //If they didn't enter a number
				std::cout << "[PLAYER 1] That is not a valid position. Please enter a new position: ";
				std::cin.clear();
				std::cin.ignore(80, '\n');
				std::cin >> move;
			}
			while(move < 1 || move > 9){ //If they entered too big or too small
				std::cout << "[PLAYER 1] That is not a valid position. Please enter a new position: ";
				std::cin >> move;
			}
			while(szUsedSpace[move-1] != 0){ //If they entered a number that was already used
				std::cout << "[PLAYER 1] That position has already been used. Please enter a different position: ";
				std::cin >> move;
			}
			board[move-1] = 'X'; //Set that spot to their value
			szUsedSpace[move-1] = 1; //Set the space as used
			totalMoves++;

			displayBoard();
		}
		else{
			std::cout << "[PLAYER 2] Please enter a position: ";
			std::cin >> move;
			while(std::cin.fail()){ //If they didn't enter a number.
				std::cout << "[PLAYER 2] That is not a valid position. Please enter a new position: ";
				std::cin.clear();
				std::cin.ignore(80, '\n');
				std::cin >> move;
			}
			while(move < 1 || move > 9){ //If they entered too big or too small. 
				std::cout << "[PLAYER 2] That is not a valid position. Please enter a new position: ";
				std::cin >> move;
			}
			while(szUsedSpace[move-1] != 0){ //If they entered a number that was already used. 
				std::cout << "[PLAYER 2] That position has already been used. Please enter a different position: ";
				std::cin >> move;
			}
			board[move-1] = 'O'; //Set that spot to their value. 
			szUsedSpace[move-1] = 1; //Set the space as used. 
			totalMoves++;

			displayBoard();
		}
	}

	return 0;
}