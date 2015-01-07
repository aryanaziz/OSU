/**********
** Program: assignment2_game.cpp
** Author: Aryan Aziz
** Description: A 2 player game where 1 player sets the number and amount of guesses and the other attempts to get it. 
** Input: answer(int), maxGuesses(int), guess(int), playAgain(char)
** Output: Game text
**********/

#include <iostream>

int answer;
int maxGuesses;
int guess;
int attempts;
int minGuess;
int maxGuess;
char playAgain;

int main() {
	do {
		attempts = 0;
		minGuess = 1;
		maxGuess = 100;
		std::cout << "[PLAYER1] Please enter a number between 1-100: ";
		std::cin >> answer;

		while (answer > 100 || answer < 1){ //If the number is not between the specified range
			std::cout << "[PLAYER1] I'm sorry, that's not in the accepted range. Please enter a number between 1-100: ";
			std::cin >> answer;
		}

		std::cout << "[PLAYER1] Please enter the number of guesses you're allowing (1-10): ";
		std::cin >> maxGuesses;

		while (maxGuesses > 10 || maxGuesses < 1){ //If the number of guesses allowed is not between 1 and 10
			std::cout << "[PLAYER1] I'm sorry, that's not in the accepted range. Please enter a number of guesses between 1-10: ";
			std::cin >> maxGuesses;
		}

		std::cout << "[PLAYER2] You have " << maxGuesses << " guesses to get the number correct. Please guess a number between " << minGuess << "-" << maxGuess << ": ";
		std::cin >> guess;
		attempts++;

		while (guess != answer && attempts < maxGuesses){ //If they get the guess wrong and they have guesses left
			if (guess > maxGuess || guess < minGuess){ //If they guess outside of the range
				std::cout <<"[PLAYER2] That was not within the range of " << minGuess << "-" << maxGuess << ". You lose an attempt for this foolishness (" << maxGuesses - attempts << " attempts remaining). Please enter a number between " << minGuess << "-" << maxGuess << ": ";
			}
			else if (guess < answer){ //Check if the guess was too low
				minGuess = guess;
				std::cout << "[PLAYER2] Uh oh, that was too low! You have " << maxGuesses - attempts << " guesses remaining. Please enter a number between " << minGuess << "-" << maxGuess << ": ";
			}
			else if (guess > answer){ //Check if the guess was too high
				maxGuess = guess;
				std::cout << "[PLAYER2] Uh oh, that was too high! You have " << maxGuesses - attempts << " guesses remaining. Please enter a number between " << minGuess << "-" << maxGuess << ": ";
			}
			attempts++;
			std::cin >> guess;
		}

		if (guess != answer && attempts >= maxGuesses){ //If they used up all of their guesses
			if ((maxGuess - answer) < (answer - minGuess)){ //If their closest guess was their lowest guess
				std::cout << "[PLAYER2] Unfortunately you were not able to guess the number " << answer << " within " << maxGuesses << " guesses. Your closest guess was " << maxGuess << "." << std::endl;
			}

			if ((maxGuess - answer) > (answer - minGuess)){ //If their closest guess was their highest guess
				std::cout << "[PLAYER2] Unfortunately you were not able to guess the number " << answer << " within " << maxGuesses << " guesses. Your closest guess was " << minGuess << "." << std::endl;
			}
		}

		if (guess == answer){ //If they got the correct answer
			std::cout << "[PLAYER2] Congratulations! You have won the game by guessing the number " << answer << " in " << attempts << " guesses!" << std::endl;
		}

		std::cout << "Play Again? (y/n) ";
		std::cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');

	return 0;
}