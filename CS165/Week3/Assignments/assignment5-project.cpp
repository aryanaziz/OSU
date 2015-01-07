/**********
** Program: assignment5_project.cpp
** Author: Aryan Aziz
** Description: Hangman Game!
** Input: word(string), guess(char)
** Output: Hangman Game Info  
**********/

#include <iostream>
#include <string>
#include <limits>

std::string word;
int maxGuesses;
int usedGuesses = 0;
std::string guess;
std::string usedLetters = "";
std::string wordDisplay;
std::string playersGuess();
std::string checkGuess();
char again;


void getWord(){ //Ask for the word and check to make sure it works. 
	std::cout << "[PLAYER1] - Please enter a word, in lowercase letters, that's less than 10 letters long: ";
	getline(std::cin, word);
	while(word.length() > 10){ //If the word is longer than 10 letters
		std::cout << "[PLAYER1] - That word has more than 10 letters. Please enter a new word: ";
		getline(std::cin, word);
	}
	while(word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos){ //If the word has letters outside of the alphabet
		std::cout << "[PLAYER1] - That is not a valid word. Please enter a new word: ";
		getline(std::cin, word);
	}
}

std::string playerGuess(){ //Request the player's guess and give info
	std::cout << std::endl << "[PLAYER2] - You have " << maxGuesses - usedGuesses << " guesses remaining to guess a " << word.size() << " letter word." << std::endl;
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
		getWord(); //Ask for the word and see if it works. 

		maxGuesses = word.length() * 2; //Set max guesses to 2x the word length. 

		checkGuess(word, maxGuesses, playerGuess()); //Ask for the guess and check the guess

		std::cout << "Play Again? (y/n) "; //Ask if you want to play again.
		std::cin >> again;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n');
		usedGuesses = 0;
		usedLetters = "";
	} while (again == 'y' || again == 'Y');

	return 0;
}