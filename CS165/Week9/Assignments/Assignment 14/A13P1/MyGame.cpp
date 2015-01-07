/*******************************************************************
* Author: Stacy Kreuziger
* class MyGame implementation file
* MyGame.cpp
*
*******************************************************************/
#include "MyGame.hpp"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <vector>
#define ROWS 22
#define COLUMNS 80

using namespace std;

Design::Design(char Rows, char Columns) 
{
    rows = Rows;
    columns = Columns;
    spot = new char*[Rows];
    for ( char i = 0; i < Rows; i++ ) 
    {
        spot[i] = new char[Columns];
    }
    for ( char i = 0; i < Rows; i++ ) 
    {
        for ( char j = 0; j < Columns; j++ ) 
        {
            spot[i][j] = '.';
        }
    }

    int choice;
    std::cout << "Which world would you like to start with? " << endl;
    std::cout << "Enter 1 for Window " << endl;
    std::cout << "Enter 2 for Block " << endl;
    std::cout << "Enter 3 for Horizontal Lines " << endl;
    std::cout << "Enter 4 for Vertical Lines" << endl;
    std::cout << "Enter 5 for Diagonals" << endl;
    std::cout << "Enter 6 for Ooooh Magic" << endl;
    while ((std::cin >> choice).fail() || std::cin.peek() != '\n' || choice < 0 || choice > 6)
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "Invalid Input. Please enter a valid integer 1 through 5. \n";
    }

    if (choice == 1)
    {
        for ( char i = 0; i < Rows; i++ )
        {
            for ( char j = 0; j < Columns; j++ ) 
            {
                if ((i == 0) ||(i == (Rows-1))|| (j == 0) || (j == (Columns-1)))
                {
                 spot[i][j] = 'X';
                }
            }
        }
    }

    else if (choice == 2)
    {
        for ( char i = 0; i < Rows; i++ ) 
        {
            for ( char j = 0; j < Columns; j++ ) 
            {
                if ((i != 0) ||(i != (Rows-1))|| (j != 0) || (j != (Columns-1)))
                {
                 spot[i][j] = 'X';
                }
            }
        }
    }

    else if (choice == 3)
    {
        for ( char i = 0; i < Rows; i++ ) 
        {
            for ( char j = 0; j < Columns; j++ ) 
            {
                if ((i%2 ==0) || (i == 0))
                {
                 spot[i][j] = 'X';
                }
            }
        }
    }

    else if (choice == 4)
    {
        for ( char i = 0; i < Rows; i++ ) 
        {
            for ( char j = 0; j < Columns; j++ ) 
            {
                if (j%2 ==0)
                {
                 spot[i][j] = 'X';
                }
            }
        }
    }

    else if (choice == 5) 
    {
        for ( char i = 0; i < Rows; i++ ) 
        {
            for ( char j = 0; j < Columns; j++ ) 
            {
                if ((i+j)%10 == 0) 
                {
                 spot[i][j] = 'X';
                }
            }
        }
    }
    
    else {
        for ( char i = 0; i < Rows; i++ ) 
        {
            for ( char j = 0; j < Columns; j++ ) 
            {
                if ((i*j)%15 == 0) 
                {
                 spot[i][j] = 'X';
                }
            }
        }
    }
}
 
Design::~Design() 
{
    for ( char i = 0; i < Rows; i++ ) 
    {
        delete[] spot[i];
    }
    delete[] spot;
}


	MyGame::MyGame( Board  bd ) : 
        board( bd) , 
        flip(true) 
{
    for ( char i = 0; i < ROWS; i++ ) 
    {
        for ( char j = 0; j < COLUMNS; j++ ) 
        {
            world[i][j] = '.';
        }
    }

    for ( char i = 0; i < board.rows; i++ ) 
    {
        for ( char j = 0; j < board.columns; j++ ) 
        {
            if ( i < ROWS && j < COLUMNS ) 
            {
                world[i][j] = board.spot[i][j];
            }
        }
    }
}
 
void MyGame::displayBoard() 
{
    if ( flip ) 
    {
        for ( char i = 0; i < ROWS; i++ ) 
        {
            for ( char j = 0; j < COLUMNS; j++ ) 
            {
                std::cout << world[i][j];
            }
            std::cout << std::endl;
        }

    } else 
    {
        for ( char i = 0; i < ROWS; i++ ) 
        {
            for ( char j = 0; j < COLUMNS; j++ ) 
            {
                std::cout << secondWorld[i][j];
            }
            std::cout << std::endl;
        }
    }

    for ( char i = 0; i < COLUMNS; i++ ) 
    {
        std::cout << '=';
    }
    std::cout << std::endl;
}

void MyGame::checkForDead() 
{
    int dead = 0;
    if (flip) 
    {
        for ( char i = 0; i < ROWS; i++ ) 
        {
            for ( char j = 0; j < COLUMNS; j++ ) 
            {
                if (world[i][j] == 'X')
                {
                    dead++;                    
                }
                if (dead > 0)
                {
                    return;
                }
            }
        }
        if (dead == 0)
            cout << "Oh no! Your world is dead! " << endl;
        flip = !flip;

    } else 
    {
        for ( char i = 0; i < ROWS; i++ ) 
        {
            for ( char j = 0; j < COLUMNS; j++ ) 
            {
                if (secondWorld[i][j] == 'X')
                {
                    dead++;                    
                }
                if (dead > 0)
                {
                    return;
                }
            }
        }
        if (dead == 0)
            cout << "Oh no! Your world is dead! " << endl;
        flip = !flip;
    }
} 

void MyGame::updateBoard() 
{
    if (flip) 
    {
        for ( char i = 0; i < ROWS; i++ ) 
        {
            for ( char j = 0; j < COLUMNS; j++ ) 
            {
                secondWorld[i][j] = MyGame::getState(world[i][j] , i , j , flip);
            }
        }
        flip = !flip;

    } else 
    {
        for ( char i = 0; i < ROWS; i++ ) 
        {
            for ( char j = 0; j < COLUMNS; j++ ) 
            {
                world[i][j] = MyGame::getState(secondWorld[i][j] , i , j , flip);
            }
        }
        flip = !flip;
    }
}
 
char MyGame::getState( char state, char yCoord, char xCoord, bool flip ) 
{
    char neighbors = 0;
    if ( flip ) 
    {
        if ((yCoord == 0) && (xCoord == 0)) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( world[ROWS-1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[ROWS-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[ROWS-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if ((yCoord == 0) && ((xCoord >0)&& (xCoord < (COLUMNS-1)))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( world[ROWS-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[ROWS-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[ROWS-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

         else if ((yCoord == 0) && (xCoord ==(COLUMNS-1))) 
         {
            char i = yCoord;
            char j = xCoord;
            if ( world[ROWS-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[ROWS-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[ROWS-1][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][0] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if ((xCoord == 0) && ((yCoord >0)&& (yCoord < (ROWS-1)))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( world[i-1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if ((xCoord == 0) && (yCoord == (ROWS-1))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( world[i-1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[0][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[0][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[0][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if (((xCoord > 0) && (xCoord < COLUMNS-1)) && (yCoord == (ROWS-1))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( world[i-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[0][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[0][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[0][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if ((yCoord == (ROWS-1)) && (xCoord == (COLUMNS-1))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( world[i-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[0][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[0][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[0][0] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if ((yCoord > 0) && (yCoord <(ROWS-1)) && (xCoord == (COLUMNS-1))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( world[i-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j] == 'X' )
            {
                neighbors++;
            }
            if ( world[i+1][0] == 'X' ) 
            {
                neighbors++;
            }
        }
        else
        {
            char i = yCoord;
            char j = xCoord;
            if ( world[i-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( world[i+1][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }
    
    } else 
    {
        if ((yCoord == 0) && (xCoord == 0)) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( secondWorld[ROWS-1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[ROWS-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[ROWS-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if ((yCoord == 0) && ((xCoord >0)&& (xCoord < (COLUMNS-1)))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( secondWorld[ROWS-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[ROWS-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[ROWS-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

         else if ((yCoord == 0) && ((xCoord >0)&& (xCoord < (COLUMNS-1)))) 
         {
            char i = yCoord;
            char j = xCoord;
            if ( secondWorld[ROWS-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[ROWS-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[ROWS-1][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][0] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if ((xCoord == 0) && ((yCoord >0)&& (yCoord < (ROWS-1)))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( secondWorld[i-1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if ((xCoord == 0) && (yCoord == (ROWS-1))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( secondWorld[i-1][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[0][COLUMNS-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[0][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[0][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if ((yCoord == (ROWS-1)) && (xCoord == (COLUMNS-1))) {
            char i = yCoord;
            char j = xCoord;
            if ( secondWorld[i-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[0][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[0][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[0][0] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if (((xCoord > 0) && (xCoord < COLUMNS-1)) && (yCoord == (ROWS-1))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( secondWorld[i-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[0][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[0][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[0][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }

        else if (((yCoord > 0) && (yCoord <(ROWS-1)) && (xCoord == (COLUMNS-1)))) 
        {
            char i = yCoord;
            char j = xCoord;
            if ( secondWorld[i-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][0] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][0] == 'X' ) 
            {
                neighbors++;
            }
        }
        else 
        {
            char i = yCoord;
            char j = xCoord;
            if ( secondWorld[i-1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i-1][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i][j+1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j-1] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j] == 'X' ) 
            {
                neighbors++;
            }
            if ( secondWorld[i+1][j+1] == 'X' ) 
            {
                neighbors++;
            }
        }
    }
    if (state == 'X') 
    {
        return ( neighbors > 1 && neighbors < 4 ) ? 'X' : '.';
    }
    else 
    {
        return ( neighbors == 3 ) ? 'X' : '.';
    }
}
 
void MyGame::iterate(int iterations ) 
{
    char keepGoing;
    for ( int i = 0; i <= iterations; i++ ) 
    {
        cout << "This is iteration " << i << endl;
        displayBoard();
        checkForDead();
        updateBoard();
        if (i != iterations)
        {
           cout << "Press X to abort, any letter/digit/symbol to continue. " << endl;
            cin >> keepGoing;
            if (keepGoing != 'X')
                continue;
            else
            {
            cout << "You have chosen to abort. Goodbye!" << endl;
            exit(1); 
            }
        }
        
    }
}
