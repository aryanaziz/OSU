/**********
** Program: A6E3.cpp
** Author: Aryan Aziz
** Description: Tic Tac Toe style program. Program ends when all spaces have been used (does not determine a winner)
** Input: move(int)
** Output: Tic Tac Toe board. 
**********/

#include <iostream>
char szBoard[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int szUsedSpace[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
int move;
int totalMoves = 0;

void displayBoard(void){ //Display the current board
	std::cout << szBoard[0] << "   " << szBoard[1] << "   " << szBoard[2] << std::endl;
	std::cout << szBoard[3] << "   " << szBoard[4] << "   " << szBoard[5] << std::endl;
	std::cout << szBoard[6] << "   " << szBoard[7] << "   " << szBoard[8] << std::endl;
}

int main() {
	displayBoard();

	while(totalMoves < 9){
		if(totalMoves % 2 == 0){
			std::cout << "[PLAYER 1] Please enter a position: ";
			std::cin >> move;
			while(std::cin.fail()){
				std::cout << "[PLAYER 1] That is not a valid position. Please enter a new position: ";
				std::cin.clear();
				std::cin.ignore(80, '\n');
				std::cin >> move;
			}
			while(move < 1 || move > 9){
				std::cout << "[PLAYER 1] That is not a valid position. Please enter a new position: ";
				std::cin >> move;
			}
			while(szUsedSpace[move-1] != 0){
				std::cout << "[PLAYER 1] That position has already been used. Please enter a different position: ";
				std::cin >> move;
			}
			szBoard[move-1] = 'X';
			szUsedSpace[move-1] = 1;
			totalMoves++;

			displayBoard();
		}
		else{
			std::cout << "[PLAYER 2] Please enter a position: ";
			std::cin >> move;
			while(std::cin.fail()){
				std::cout << "[PLAYER 2] That is not a valid position. Please enter a new position: ";
				std::cin.clear();
				std::cin.ignore(80, '\n');
				std::cin >> move;
			}
			while(move < 1 || move > 9){
				std::cout << "[PLAYER 2] That is not a valid position. Please enter a new position: ";
				std::cin >> move;
			}
			while(szUsedSpace[move-1] != 0){
				std::cout << "[PLAYER 2] That position has already been used. Please enter a different position: ";
				std::cin >> move;
			}
			szBoard[move-1] = 'O';
			szUsedSpace[move-1] = 1;
			totalMoves++;

			displayBoard();
		}
	}

	return 0;
}