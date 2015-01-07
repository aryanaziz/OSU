/**********
** Program: A10P1.cpp
** Author: Aryan Aziz
** Description: Let's the user choose what game they want and play the game! 
** Input: gameChoice(string), again(char), and the ingame variables
** Output: Game results. 
**********/

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

std::string gameChoice;
std::string wordsArray[] = {"the", "man", "goes", "to", "the", "beach", "and", "got", "some", "food", "eat", "while", "running"};
int usedNumberArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char again;

class numberGuessClass {
	private:
		int answer;
		int maxGuesses;
		int guess;
		int attempts;
		int minGuess;
		int maxGuess;
	public: 
		void numberGuessGame(void) {
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
		}
};

class wordGuessClass {
	private:
		std::string word;
		int maxGuesses;
		int usedGuesses;
		std::string guess;
		std::string usedLetters;
		std::string wordDisplay;
		std::string playersGuess();
		std::string checkGuess();
	public:
		void wordGuessGame(void) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n');
			getWord();
			usedGuesses = 0;
			usedLetters = "";
			maxGuesses = word.length() * 2;
			checkGuess(word, maxGuesses, playerGuess());
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n');
			usedGuesses = 0;
			usedLetters = "";
		}
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
};

class phraseGuessClass {
	private:
		
		std::string phrase;
		int randomNum;
		int theNumber;
		
		int maxGuesses;
		int usedGuesses;
		std::string guess;
		std::string usedLetters;
		std::string wordDisplay;
		std::string playersGuess();
		std::string checkGuess();
	public:
		void phraseGuessGame(void) {
			usedGuesses = 0;
			usedLetters = "";
			getPhrase();
			maxGuesses = phrase.length() * 2;
			checkGuess(phrase, maxGuesses, playerGuess());
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n');
			usedGuesses = 0;
			usedLetters = "";
		}
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
};






int main() {

	numberGuessClass numberGuessObject;
	wordGuessClass wordGuessObject;
	phraseGuessClass phraseGuessObject;


	do {
		std::cout << "Hello and welcome to the game arena! Which game would you like to play?" << std::endl;
		std::cout << "1. Number Guess" << std::endl;
		std::cout << "2. Word Guess" << std::endl;
		std::cout << "3. Phrase Guess" << std::endl;

		std::cin >> gameChoice;
		while(gameChoice.length() > 1 || gameChoice.length() < 1) {
			std::cout << "That is not a correct choice, please select 1, 2, or 3" << std::endl;
			std::cin >> gameChoice;
		}

		while(gameChoice[0] != '1' && gameChoice[0] != '2' && gameChoice[0] != '3') {
			std::cout << "That is not a correct choice, please select 1, 2, or 3" << std::endl;
			std::cin >> gameChoice;
		}

		if(gameChoice[0] == '1') {
			numberGuessObject.numberGuessGame();
		}

		else if(gameChoice[0] == '2') {
			wordGuessObject.wordGuessGame();
		}

		else {
			phraseGuessObject.phraseGuessGame();
		}


		std::cout << "Play Again? (y/n) "; //Ask if you want to play again.
		std::cin >> again;
		std::cin.ignore();
		std::cin.clear();
	} while (again == 'y' || again == 'Y');

	return 0;
}