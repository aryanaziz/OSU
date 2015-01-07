/*******************************************************************
* Author: Stacy Kreuziger
* class MyGame interface file
* MyGame.cpp
*
*******************************************************************/

#ifndef MYGAME_HPP
#define MYGAME_HPP

#define ROWS 22
#define COLUMNS 80

    struct Board {
    public:
        char rows;
        char columns;
        char **spot;
    };

    struct Design : public Board {
        static const char Rows = 22;
        static const char Columns = 80;
        Design(char Rows, char Columns);
        ~Design();
    };

	class MyGame
	{
		public:
    		MyGame( Board  bd );
    		void displayBoard();
    		void checkForDead();
    		void updateBoard();
    		char getState( char state , char xCoord , char yCoord , bool flip);
    		void iterate(int iterations);
		private:
    		char world[ROWS][COLUMNS];
    		char secondWorld[ROWS][COLUMNS];
    		bool flip;
    		Board board;
	};

#endif //MYGAME_HPP