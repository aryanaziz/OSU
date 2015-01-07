/**********
** Program: A6P1.cpp
** Author: Aryan Aziz
** Description: Hang man style of game with phrases instead of words. 
** Input: guess(char)
** Output: Hangman Game info.
**********/

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

std::string wordsArray[] = {"the", "man", "goes", "to", "the", "beach", "and", "got", "some", "food", "eat", "while", "running"};
std::string phrase;
int randomNum;
int theNumber;
int usedNumberArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int maxGuesses;
int usedGuesses = 0;
std::string guess;
std::string usedLetters = "";
std::string wordDisplay;
std::string playersGuess();
std::string checkGuess();
char again;

int rand_int(void){
	srand(time(0)); //Seeds the rand function so that a different random number is chosen every second (otherwise the same random number will popup for the same range)
	randomNum = rand() % 13 + 1; //Creates a random number
	return randomNum; //Returns that number
}

std::string getPhrase(void){
	for (int i = 0; i < 3; i++){
		theNumber = rand_int();
		while(usedNumberArray[theNumber - 1] == 1){
			theNumber = rand_int();
		}
		usedNumberArray[theNumber - 1] = 1;
		phrase.append(wordsArray[rand_int() - 1]);
	}
	return phrase;
}


std::string playerGuess(){ //Request the player's guess and give info
	std::cout << std::endl << "[PLAYER2] - You have " << maxGuesses - usedGuesses << " guesses remaining to guess a " << phrase.size() << " letter word." << std::endl;
	std::cout << "[PLAYER2] - Letters used: " << usedLetters << std::endl;
	std::cout << "[PLAYER2] - Please enter a guess: ";
	std::cin >> guess;

	while(usedLetters.find(guess) != std::string::npos){ //If they have already guessed the letter previously
		std::cout << "[PLAYER2] - You have already guessed " << guess << ". Please enter another guess: ";
		std::cin >> guess;
	}	

	usedLetters += guess; //Add to the used letters string
	usedGuesses++; //Add a guess
	return guess;
}

void checkGuess(std::string word, int maxGuesses, std::string guess){
	std::string guessedWord(word.size(), '_');

	while(maxGuesses != usedGuesses && guessedWord != word){ //While they have guesses left and they havent guessed the word
		if(word.find(guess) != std::string::npos){ //If the guess is correct
			std::cout << "[PLAYER2] - Yes, " << guess << " exists in the word" << std::endl;

			for(int i = 0; i < word.length(); i++){
				if(word[i] == guess[0]){
					guessedWord[i] = guess[0]; //Add the guess to the word
				}
			}

			std::cout << "[PLAYER2] - So far, you have: " << guessedWord << std::endl;

			if(guessedWord != word){ //If they haven't gotten the word yet, ask for another guess
				guess = playerGuess();
			}
		}
		else { //If the guess isn't correct
			std::cout << "[PLAYER2] - Sorry, " << guess << " does not exist in the word." << std::endl;
			if(guessedWord != word){ //If they haven't gotten the word yet, ask for another guess
				guess = playerGuess();
			}
		}
	}
	if(maxGuesses == usedGuesses && guessedWord != word){ //If they hit their limit and haven't guessed the word
		std::cout << "[PLAYER2] - Sorry you lost" << std::endl;
		std::cout << "[PLAYER2] - The word was: " << word << std::endl;
		std::cout << "[PLAYER2] - You had: " << guessedWord << std::endl;
	}
	else {
		std::cout << "[PLAYER2] - You win!" << std::endl; //winner!
	}
}


int main(){
	do {
		getPhrase(); //Ask for the word and see if it works. 

		maxGuesses = phrase.length() * 2; //Set max guesses to 2x the word length. 

		checkGuess(phrase, maxGuesses, playerGuess()); //Ask for the guess and check the guess

		std::cout << "Play Again? (y/n) "; //Ask if you want to play again.
		std::cin >> again;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n');
		usedGuesses = 0;
		usedLetters = "";
	} while (again == 'y' || again == 'Y');

	return 0;
}