/* CS344 - Assignment 2 - Adventure */
/* Author: Aryan Aziz */

//Header Files
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>


//Defining Global Variables
char input[4]; //User Input
char dirName[50]; //String for the directory name
char *availRooms[] = {"SAC", "LAL", "LAC", "SAS", "GSW", "PHX", "UTA", "HOU", "DAL", "MEM"}; //Hardcoded room values
char *rooms[7]; //Array for holding room list, used in file generation
char filePath[100]; //Strong for holding the entire filepath
int tempArr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Temporary array to store the # of connections for each room
int i = 0; //Used through for loops
int connectionMatrix[7][7] = {0}; //To help keep track of connections, 2x2 matrix of rooms
int end = 0;
char *moves[100]; //Store every move. Figure if it takes you more than 100 moves to get to the end of a 7 room maze you need help
int numMoves = 0; //Store the # of moves. 


//Gets the actual players input on a turn and places it into "input".
void playerInput(void) {
	fflush(stdin);
	scanf("%s", input);
	fflush(stdin);
	fflush(stdout);
	//Might not be necessary to do all this flushing, but I was getting errors so I went buckwild with them
}

//Creates the directory
void createFolder(void) {
	sprintf(dirName,"aziza.rooms.%d", getpid());
	mkdir(dirName, 700);
}

//Creates each of the room files
void createRooms(void) {
	while(i < 7) {
		int randomNumber;
		randomNumber = rand() % 10; //Create a random number between 0-9
		while(tempArr[randomNumber] == 0) { //Make sure that the room hasn't been used already
			sprintf(filePath,"%s/%s", dirName, availRooms[randomNumber]); //Create the full file path
			FILE *fp;
			fp = fopen(filePath, "a");
			fprintf(fp, "ROOM NAME: %s\n", availRooms[randomNumber]); //Add the room name to the file
			fclose(fp);
			rooms[i] = availRooms[randomNumber]; //Place into array for later use
			tempArr[randomNumber] = 1; //Set the room as used
			i++; //On to the next one
		}
	}
}

//Creates each of the connections
void createConnections(void) {
	for(i = 0; i < 7; i++) {
		int numConnections;
		numConnections = (rand() % 4) + 3; //Random number between (0-3) + 3. (so 3-6)
		int j;
		int sum = 0;
		for(j = 0; j < 7; j++) {
			sum = sum + connectionMatrix[i][j]; //Find out how many connections the room currently has
		}
		while(sum < numConnections + 1) { //If there are any unused connections
			int randomRoom;
			randomRoom = rand() % 7; //Pick a random room
			while(randomRoom == i) { //Make sure it's not the room we are already on
				randomRoom = rand() % 7; 
			}
			connectionMatrix[i][randomRoom] = 1; //Set that connection
			connectionMatrix[randomRoom][i] = 1; //Naturally, set the opposite connection too
			sum = sum + 1;
		}
	}
}

//After connections are created, write them to the file
void writeConnections(void) {
	for(i = 0; i < 7; i++) {
		int numConnections = 1;
		int j;
		for(j = 0; j < 7; j++) {
			if(connectionMatrix[i][j] == 1) { //If that position on the matrix has a connection, write it
				sprintf(filePath,"%s/%s", dirName, rooms[i]);
				FILE *fp;
				fp = fopen(filePath, "a");
				fprintf(fp, "CONNECTION %d: %s\n", numConnections, rooms[j]);
				fclose(fp);
				numConnections = numConnections + 1;
			}
		}
	}
}

//Lastly, write the type of room to the files
//Since I assigned rooms at random, I said that the first room I created is beginning, last is end, and everything else is mid.
void writeType(void) {
	for(i = 0; i < 7; i++) {
		sprintf(filePath,"%s/%s", dirName, rooms[i]);
		FILE *fp;
		fp = fopen(filePath, "a");
		if(i == 0) {
			fprintf(fp, "ROOM TYPE: START_ROOM\n");
		}
		else if(i == 6) {
			fprintf(fp, "ROOM TYPE: END_ROOM\n");
		}
		else {
			fprintf(fp, "ROOM TYPE: MID_ROOM\n");
		}
		fclose(fp);
	}
}


//Prototype, defined below
void checkForEnd(int);


//The actual turns being done
void playerTurn(int roomIndex) { //Current room
	if(end == 1) { //If we reached the end
		fflush(stdout);
		return; //End the function
	}
	else {
		if(roomIndex != 0) { //We want a new line BETWEEN turns, not at the beginning
			printf("\n");
		}
		checkForEnd(roomIndex); //Check if this room is the end
		if(end == 1) { //If it is, end it
			fflush(stdout);
			return;
		}
		int validMove = 1;
		while(validMove == 1) {
			sprintf(filePath,"%s/%s", dirName, rooms[roomIndex]); //Grab information on the current room

			//Get the number of lines in the room's file
			FILE *fp;
			fp = fopen(filePath, "r");
			int numLines = 0;
			char line[256];
			while(fgets(line, sizeof line, fp) != NULL) {
				numLines++;
			}
			fclose(fp);

			//Get the actual info in the room's file
			fp = fopen(filePath, "r");
			int currentLine = 0;
			char *possibleRooms[6][3]; //Possible rooms, 6 possible connections, rooms are 3 letters
			while(fgets(line, sizeof line, fp) != NULL) {
				if(currentLine == 0) { //First line in the file
					char substr[4];
					strncpy(substr, line+11, 3); //Just grab the room name from that line
					substr[3] = '\0';
					printf("CURRENT LOCATION: %s\n", substr); //Output to screen
				}
				else if(currentLine == 1) { //If it's the first connection (so that I can output the string too)
					printf("POSSIBLE CONNECTIONS: ");
					fflush(stdout);
					char substr[4];
					strncpy(substr, line+14, 3); //Grab the connection's room
					substr[3] = '\0';
					printf("%s", substr);
					strcpy(possibleRooms[currentLine - 1], substr); //Place it into array of possible rooms
				}
				else if(currentLine > 1 && currentLine < numLines - 1) { //If it's any other connection
					printf(", ");
					fflush(stdout);
					char substr[4];
					strncpy(substr, line+14, 3); //Grab the connection's room
					substr[3] = '\0';
					printf("%s", substr);
					fflush(stdout);
					strcpy(possibleRooms[currentLine - 1], substr); //Place it into array of possible rooms
				}
				else {
					printf(".");
					fflush(stdout);
				}
				currentLine++;
			}
			fclose(fp);	
			printf("\nWHERE TO? >");

		
			playerInput(); //Grab player's input
			for(i = 0; i < numLines - 2; i++) { //Iterate through number of connections
				if(strcmp(possibleRooms[i], input) == 0) { //If the player entered a valid room
					int j;
					for(j = 0; j < 7; j++) {
						if(strcmp(rooms[j], input) == 0) { //Find out which room it is
							playerTurn(j); //Run the entire player turn function at that next room
						}
					}
					validMove = 0; //Set valid move to 0 to end the while loop
				}
			}
			if(validMove == 1) { //If it got here, that mean's that the input was invalid
				printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
				fflush(stdout);
				fflush(stdin);
			}
		}
	}
}

//Check's if the current room is the end room
void checkForEnd(int roomIndex) {
	numMoves++; //Increase the number of moves
	moves[numMoves - 1] = rooms[roomIndex]; //Hold the room name so we can output at the end
	
	sprintf(filePath,"%s/%s", dirName, rooms[roomIndex]);
	char substr[4];
	int currentLine = 1;

	FILE *fp;
	fp = fopen(filePath, "r");
	int numLines = 0;
	char line[256];
	while(fgets(line, sizeof line, fp) != NULL) {
		numLines++;
	}
	fclose(fp);

	fp = fopen(filePath, "r");
	while(fgets(line, sizeof line, fp) != NULL) {
		if(currentLine == numLines) {
			strncpy(substr, line+11, 3);
			substr[3] = '\0';
		}
		currentLine++;
	}

	//Check if the string we pulled above says "END"
	if(strncmp(substr, "END", 3) == 0) {
		end = 1; //If it does, set the end value to 1 so that player turn finishes too. 
	}
}

int main() {
	srand(time(NULL)); //Seed random number

	//Function calls
	createFolder();
	createRooms();
	createConnections();
	writeConnections();
	writeType();

	playerTurn(0);
	printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", numMoves - 1);
	for(i = 1; i < numMoves; i++) {
		printf("%s\n", moves[i]);
	}

	return 0;
}	