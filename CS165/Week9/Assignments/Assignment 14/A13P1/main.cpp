/*******************************************************************
* Author: Stacy Kreuziger
* Date Created: 23 May 2014
* Last Modified: 25 May 2014
* File Name: A13P1.cpp
*
* Overview:
*   This program is Assignment 13 Project 1. The task for this project
* is to write the code that implements our design for Conway's Game of
* Life.  The user must be provided start up options, must be able to
* choose how many times to run the program (in other words iterate),
* and must be given the option to abort.
*
*******************************************************************/

#include <iostream>
#include <cstdlib>
#include <limits>
#include <vector>
#include "MyGame.hpp"
 
using namespace std;


 
int main() {
    int userIterate;
    Design design(22, 80);
    MyGame game(design);
    cout << "How many times would you like to iterate? Please choose a positive value of 100 or less. " << endl;
    while ((cin >> userIterate).fail() || cin.peek() != '\n' || userIterate < 0 || userIterate > 100)
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "Invalid Input. Please enter a valid integer greater than zero and less than 101. \n";
    }
    game.iterate(userIterate);
    cout << "That's the end of the game. Thanks for playing. Goodbye. " << endl;
}
