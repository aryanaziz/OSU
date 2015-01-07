/***********************************************************
* Author: Taylor Jenkins
* Date Created: 5/24/14
* Last Modification Date: 5/24/14
* File name: A13E4.cpp
*
* Overview: This is my implementation of Conway's "The Game of Life".
*
* Input:	int lifespan, life_cycles, pattern_choice;
*
* Output:	Progression of the Game of Life is displayed on the screen.
* 
* Sources used:
*	CS165 Assignment document
*	Absolute C++ Fifth Edition
************************************************************/
#include <iostream>
using std::cout;
using std::cin;
using std::getline;
using std::endl;

#include <string>
using std::string;

#include <climits>
#include <ctime>
#include <cstdlib>

#define WORLD_X 80
#define WORLD_Y 22
#define WORLD_Z 2

// Timed delay function
void delay(int ticks);

// assigns a user input integer in the specified range
// and outputs an appropriate error message
void getInt(int &input, int min = INT_MIN, int max = INT_MAX, string bad_input = "Invalid Entry");

// Takes an x value that may or may not be out of the range of indexes
// for WorldArray[x][y][0] and returns the appropriate in range x value.
int xpos(int x);

// Takes an y value that may or may not be out of the range of indexes
// for WorldArray[x][y][0] and returns the appropriate in range y value.
int ypos(int y);

// count neighbors of WorldArray[x][y][0] at position x,y
void countNeighbors(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y);

// count neighbors of WorldArray[x][y][0] at each position in the array.
void countNeighbors(int WorldArray[][WORLD_Y][WORLD_Z]);

// Updates the status of life in the cell at x, y of WorldArray[x][y][0]
void updateWorld(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y);

// Clear Screen
void clearScreen();

// Prints the world to the screen.
void printWorld(int WorldArray[][WORLD_Y][WORLD_Z]);

// Initialize a Blinker pattern at position x,y
void blinker(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y);

// Initialize a block pattern at position x,y
void block(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y);

// Initialize a loaf pattern at position x,y
void loaf(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y);

// Initialize a Right and Downward Moving Glider pattern at position x,y
void rd_glider(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y);

// Initialize a Left and Upward Moving Glider pattern at position x,y
void lu_glider(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y);

// Randomly initialize a 10 x 10 grid at position x,y.
void rand_grid(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y);

// Randomly initialize the world.
void rand_init_world(int WorldArray[][WORLD_Y][WORLD_Z]);

// converts lowercase characters in a string to uppercase.
string UpperCase(string& str);

// Compares a string and returns true if it is a y or a yes.
bool IsYes(string& yesString);

// Compares a string and returns true if it is a N or a NO.
bool IsNo(string& noString);

// Returns true if the user chooses to play again, 
// and returns false if the user chooses to quit.
bool playAgain();

// Compares str1 and str2 then returns true if they are the same.
bool sameString(string str1, string str2);

int main()
{
	int lifespan, life_cycles, pattern_choice;
	int WorldArray[WORLD_X][WORLD_Y][WORLD_Z];
	
	srand(time(NULL));
		
	do
	{	// Get input for lifespan of a generation.
		cout << "please enter the length of time each generation should last, in milliseconds.\n";
		getInt(lifespan, 0, 3000);
		cout << endl;
		
		// Get input for the number of life_cycles to execute in the program.
		cout << "Please enter the number of generations the game should last.\n";
		getInt(life_cycles, 0, 1000);
		cout << endl;
		
		// get input for pattern_choice to initialize the game.
		cout << "How would you like to initialize the game?\n"
			 << "   1: Initialize with a random pattern.\n"
			 << "   2: Initialize with a blinker pattern.\n"
			 << "   3: Initialize with a block pattern.\n"
			 << "   4: Initialize with a loaf pattern.\n"
			 << "   5: Initialize with a  right and downward moving glider.\n"
			 << "   6: Initialize with a  left and upward moving glider.\n"
			 << endl;
		getInt(pattern_choice, 1, 6, "That was not a valid choice");
		
		//Create an array representing the world and initialize to zeroes.
		for (int x=0; x<WORLD_X; x++)
		{	for (int y=0; y<WORLD_Y; y++)
			{	WorldArray[x][y][0] = 0;
				WorldArray[x][y][1] = 0;
			}
		}
		
		// Initialize the array based on the menu selection.
		switch (pattern_choice)
		{	case 1:
				rand_init_world(WorldArray);
				break;
			case 2:
				blinker(WorldArray, 4, 5);
				break;
			case 3:
				block(WorldArray, 4, 4);
				break;
			case 4:
				loaf(WorldArray, 3, 3);
				break;
			case 5:
				rd_glider(WorldArray, 70, 18);
				break;
			case 6:
				lu_glider(WorldArray, 1, 5);
				break;
			default:
				rand_grid(WorldArray, 35, 5);				
		}
		
		clearScreen();
		printWorld(WorldArray);
		delay(lifespan);
			
		// generate cycles of life
		for (int i=0; i<life_cycles; i++)
		{	countNeighbors(WorldArray);
			for (int x=0; x<WORLD_X; x++)
			{	for (int y=0; y<WORLD_Y; y++)
				{	updateWorld(WorldArray, x, y);
				}
			}
			clearScreen();
			printWorld(WorldArray);
			delay(lifespan);
		}
		
		
	} while (playAgain());
	
	return 0;
}

/*// Timed delay function (1 tick = 1 second)
void delay(int ticks)
{
	int resume_time;
	resume_time = static_cast<int>(time(NULL)) + ticks;
	while (static_cast<int>(time(NULL)) < resume_time)
	{	// timed delay
	}
}*/

// Timed delay function (1000 ticks = 1 millisecond)
void delay(int ticks)
{
	int delay_ticks;
	delay_ticks = static_cast<int>(clock()) + (ticks*CLOCKS_PER_SEC/1000);
	while (static_cast<int>(clock()) < delay_ticks)
	{	// timed delay
	}
}

// assigns a user input integer in the specified range
// and outputs an appropriate error message
void getInt(int &input, int min, int max, string bad_input)
{
	bool valid = false;
	do
	{	cout << "Enter an integer from " << min << " to " << max << ": ";
		cin >> input;
		if((!cin) || (cin.peek() != '\n') || input < min || input > max)// checks if cin is not a valid int.
		{	cin.clear(); 						// clears the cin error state.
			cin.ignore(INT_MAX, '\n');  		// Empties the input stream.
			cout << bad_input << endl;
			valid = false;
		}
		else
		{ valid = true;
		}
	} while (!valid);
}

// Takes an x value that may or may not be out of the range of indexes
// for WorldArray[x][y][0] and returns the appropriate in range x value.
int xpos(int x)
{
	const int MAX_X = WORLD_X-1;
	const int MIN_X = 0;
	while (x < MIN_X || x > MAX_X)
	{	if (x > MAX_X)
			x = x - (MAX_X+1);
		else if (x < MIN_X)
			x = x + (MAX_X+1);
	}
	return x;
}

// Takes an y value that may or may not be out of the range of indexes
// for WorldArray[x][y][0] and returns the appropriate in range y value.
int ypos(int y)
{
	const int MAX_Y = WORLD_Y-1;
	const int MIN_Y = 0;
	while (y < MIN_Y || y > MAX_Y)
	{	if (y > MAX_Y)
			y = y - (MAX_Y+1);
		else if (y < MIN_Y)
			y = y + (MAX_Y+1);
	}
	return y;
}

// count neighbors of WorldArray[x][y][0] at position x,y
void countNeighbors(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y)
{
	WorldArray[x][y][1] = 0;
	for (int i=-1; i<2; i++)
	{	for (int j=-1; j<2; j++)
		{	if (i != 0 || j != 0)
				WorldArray[x][y][1] += WorldArray[xpos(x+i)][ypos(y+j)][0];
		}
	}
}

// count neighbors of WorldArray[x][y][0] at each position in the array.
void countNeighbors(int WorldArray[][WORLD_Y][WORLD_Z])
{
	for (int i=0; i<WORLD_X; i++)
	{	for (int j=0; j<WORLD_Y; j++)
		{	countNeighbors(WorldArray, i, j);
		}
	}
}

// Updates the status of life in the cell at x, y of WorldArray[x][y][0]
void updateWorld(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y)
{
	// Death occurs
	if (WorldArray[x][y][1] < 2 || WorldArray[x][y][1] > 3)
	{	WorldArray[x][y][0] = 0;
	}
	// Birth Occurs
	else if (WorldArray[x][y][1] == 3)
	{	WorldArray[x][y][0] = 1;
	}
}

// Clear Screen
void clearScreen()
{
	for (int i=0; i<100; i++)
	{	cout << endl;
	}
}

// Prints the world to the screen.
void printWorld(int WorldArray[][WORLD_Y][WORLD_Z])
{
	for (int y=0; y<WORLD_Y; y++)
	{	for (int x=0; x<WORLD_X; x++)
		{	if (WorldArray[x][y][0] == 1)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
}

// Initialize a Blinker pattern at position x,y
void blinker(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y)
{
	WorldArray[xpos(x+0)][ypos(y)][0] = 1;
	WorldArray[xpos(x+1)][ypos(y)][0] = 1;
	WorldArray[xpos(x+2)][ypos(y)][0] = 1;
}

// Initialize a block pattern at position x,y
void block(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y)
{
	WorldArray[xpos(x+0)][ypos(y+0)][0] = 1;
	WorldArray[xpos(x+1)][ypos(y+0)][0] = 1;
	WorldArray[xpos(x+0)][ypos(y+1)][0] = 1;
	WorldArray[xpos(x+1)][ypos(y+1)][0] = 1;
}

// Initialize a loaf pattern at position x,y
void loaf(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y)
{
	WorldArray[xpos(x+1)][ypos(y+0)][0] = 1;
	WorldArray[xpos(x+2)][ypos(y+0)][0] = 1;
	WorldArray[xpos(x+0)][ypos(y+1)][0] = 1;
	WorldArray[xpos(x+3)][ypos(y+1)][0] = 1;
	WorldArray[xpos(x+1)][ypos(y+2)][0] = 1;
	WorldArray[xpos(x+3)][ypos(y+2)][0] = 1;
	WorldArray[xpos(x+2)][ypos(y+3)][0] = 1;
}

// Initialize a Right and Downward Moving Glider pattern at position x,y
void rd_glider(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y)
{
	WorldArray[xpos(x+1)][ypos(y+0)][0] = 1;
	WorldArray[xpos(x+2)][ypos(y+1)][0] = 1;
	WorldArray[xpos(x+0)][ypos(y+2)][0] = 1;
	WorldArray[xpos(x+1)][ypos(y+2)][0] = 1;
	WorldArray[xpos(x+2)][ypos(y+2)][0] = 1;
}

// Initialize a Left and Upward Moving Glider pattern at position x,y
void lu_glider(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y)
{
	WorldArray[xpos(x+0)][ypos(y+0)][0] = 1;
	WorldArray[xpos(x+1)][ypos(y+0)][0] = 1;
	WorldArray[xpos(x+2)][ypos(y+0)][0] = 1;
	WorldArray[xpos(x+0)][ypos(y+1)][0] = 1;
	WorldArray[xpos(x+1)][ypos(y+2)][0] = 1;
}

// Randomly initialize a 10 x 10 grid at position x,y.
void rand_grid(int WorldArray[][WORLD_Y][WORLD_Z], int x, int y)
{
	for (int i=0; i<10; i++)
	{	for (int j=0; j<10; j++)
		{	if (rand()%3 == 1)
			{	WorldArray[xpos(x+i)][ypos(y+j)][0] = 1;
			}
		}
	}
}

// Randomly initialize the world.
void rand_init_world(int WorldArray[][WORLD_Y][WORLD_Z])
{
	for (int x=0; x<8; x++)
	{	for (int y=0; y<2; y++)
		{	switch (rand()%7 + 1)
			{	case 1:
					blinker(WorldArray, (x*10 + 4), (y*10 + 5));
					break;
				case 2:
					block(WorldArray, (x*10 + 4), (y*10 + 4));
					break;
				case 3:
					loaf(WorldArray, (x*10 + 3), (y*10 + 3));
					break;
				case 4:
					rd_glider(WorldArray, (x*10 + 3), (y*10 + 3));
					break;
				case 5:
					lu_glider(WorldArray, (x*10 + 5), (y*10 + 5));
					break;
				default:
					rand_grid(WorldArray, (x*10), (y*10));				
			}
		}
	}
}

// converts lowercase characters in a string to uppercase.
string UpperCase(string& str)
{
	string tempString(str);
	for (unsigned int i=0; i<str.length(); i++)
		tempString[i] = toupper(str[i]);
	return tempString;
}

// Compares a string and returns true if it is a y or a yes.
bool IsYes(string& yesString)
{	
	string strA = "Y";
	string strB = "YES";
	string str = UpperCase(yesString);
	return sameString(str, strA) || sameString(str, strB);
}

// Compares a string and returns true if it is a N or a NO.
bool IsNo(string& noString)
{
	string strA = "N";
	string strB = "NO";
	string str = UpperCase(noString);
	return sameString(str, strA) || sameString(str, strB);
}

// Compares str1 and str2 then returns true if they are the same.
bool sameString(string str1, string str2)
{
	bool sameContent = str1.length() == str2.length();
	for (unsigned int i=0; (i < str1.length()) && (sameContent); i++)
	{
		sameContent = str1.at(i) == str2.at(i);
	}
	return sameContent;
}

// Returns true if the user chooses to play again, 
// and returns false if the user chooses to quit.
bool playAgain()
{
	string goAgain;
	bool yesAnswer;
	bool noAnswer;
	do
	{
		cout << "Would you like to play again? Enter Y/N. ";
		cin >> goAgain;
		cout << endl;
		yesAnswer = IsYes(goAgain);
		noAnswer = IsNo(goAgain);
		cin.clear(); 						// clears the cin error state.
		cin.ignore(INT_MAX, '\n');  		// Empties the input stream.
	} while (!yesAnswer && !noAnswer);
	return yesAnswer;
}