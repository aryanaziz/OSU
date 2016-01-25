//OTP Encode - Client
//Author: Aryan Aziz
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

//Get File Function
int getFile(int socket, int processId) {
	char fr_name[10];
	bzero(fr_name, 10);
	char receivedMessage[10];
	sprintf(fr_name, "%dt", processId);
	FILE *fr = fopen(fr_name, "a"); //Create a temporary file to store the textfile
	int fr_block_sz = 0; 
	while((fr_block_sz = recv(socket, receivedMessage, 10, 0)) > 0) { //Get the chunks
		int write_sz = fwrite(receivedMessage, sizeof(char), fr_block_sz, fr); //Write to the file
		if(write_sz < fr_block_sz) {
		    //printf("File write failed on server.\n");
		}
		bzero(receivedMessage, 10);
		if (fr_block_sz == 0 || fr_block_sz != 10) { //If we got anything less than a full size chunk, it's probably the last one
		    break;
		}
	}
	fclose(fr);
	FILE *text = fopen(fr_name, "r");
	fseek(text, 0, SEEK_END);
	int numChars = ftell(text);
	//printf("File '%s' Transfer Complete\n", fr_name);
	return numChars; //Return the number of characters, used in arrays later
}

//Get Key Function
void getKey(int socket, int processId) {
	char fr_name[10];
	bzero(fr_name, 10);
	char receivedMessage[10];
	sprintf(fr_name, "%dk", processId);
	FILE *fr = fopen(fr_name, "a"); //Create a temporary file to store the keyfile
	int fr_block_sz = 0; 
	while((fr_block_sz = recv(socket, receivedMessage, 10, 0)) > 0) { //Get the Chunks
		int write_sz = fwrite(receivedMessage, sizeof(char), fr_block_sz, fr); //Write to the file
		if(write_sz < fr_block_sz) {
		    //printf("File write failed on server.\n");
		}
		bzero(receivedMessage, 10);
		if (fr_block_sz == 0 || fr_block_sz != 10) { //If we got anything less than a full size chunk, it's probably the last one
		    break;
		}
	}
	fclose(fr);
	//printf("File '%s' Transfer Complete\n", fr_name);
	return;
}

//Encode function, actually processes, encodes, and sends to client
void encode(int processId, int numChars, int socket) {
	char fileArray[numChars - 1]; //-1 because of the newline char at the end of the file
	char keyArray[numChars - 1]; //Same as above
	char encodedArray[numChars - 1];
	int i = 0;
	int c;

	char fr_name[10];
	bzero(fr_name, 10);
	sprintf(fr_name, "%dt", processId);

	FILE *fr = fopen(fr_name, "r"); //Open the text file
	while((c = fgetc(fr)) != EOF && i < numChars - 1) { //Read it in char by char
		fileArray[i] = c; //Write it to the array
		i++;
	}
	fclose(fr);


	char kr_name[10];
	bzero(kr_name, 10);
	sprintf(kr_name, "%dk", processId);

	int j = 0;
	int d;
	FILE *kr = fopen(kr_name, "r"); //Open the key file
	while((d = fgetc(kr)) != EOF && j < numChars - 1) { //Read it in char by char
		keyArray[j] = d; //Write it to the array
		j++;
	}
	fclose(kr);
	//char letters[27] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
	char letters[28];
	sprintf(letters, " ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	

	for(i = 0; i < numChars - 1; i++) { //Loop through the message
		int sum = 0;
		for(j = 0; j < 28; j++) { //Loop through the possible letters
			if(fileArray[i] == letters[j]) { //If an item matches a letter
				sum = sum + j; //Add its position to the sum
			}
			if(keyArray[i] == letters[j]) { //And if a key item matches a letter
				sum = sum - j; //Remove its position to the sum
			}
		}
		sum = sum - 1; //Subtract 1 from the sum
		if(sum < 0) { //If the sum is less than 0
			sum = sum + 27; //add 27 to it (modulo)
		}
		encodedArray[i] = letters[sum]; //Record the decoded array (I'm aware that the variable is still called encoded array)
	}

	//printf("%s", encodedArray);

	//Send the message back to the server
	char encodedMessage[numChars];
	bzero(encodedMessage, numChars);
	sprintf(encodedArray, "%s\0", encodedArray);
	//encodedArray[numChars - 1] = "\n";
	//printf("\n%s", encodedArray);
	int n = write(socket,encodedArray,numChars - 1); //Send it Back
	unlink(fr_name); //delete the temp file
	unlink(kr_name); //delete the temp file
	return;
}

//New Process function, handles all of the main items
void newThread(int socket, int processId) {
	int n;
	char type[2];
	bzero(type, 2);
	sprintf(type, "d");
	n = write(socket,type,strlen(type)); //Authenticate that it's decode server
	//printf("Getting file from pid %d\n", processId);
	int numChars = getFile(socket, processId); //Get the file and store number of chars
	char confirmation[2];
  	bzero(confirmation,1);
  	sprintf(confirmation, "1");
  	n = write(socket,confirmation,strlen(confirmation)); //Tell the client to move on
	//printf("Getting key from pid %d\n", processId);
	getKey(socket, processId); //Get the key file
	encode(processId, numChars, socket); //Call the encode function
	//char message[37];
	//bzero(message, 37);
	//sprintf(message, "THE RED GOOSE FLIES AT MIDNIGHT STOP");
	/*n = write(socket,message,strlen(message));*/
	close(socket); //Close the socket
	return;
}

int main(int argc, char *argv[]) {
	int sockfd; //Listen on this one (file descriptor)
	int newsockfd; //Connect on this one (file descriptor)
	int portNum; //Port number
	int processId; //Process id

	socklen_t clilen; //Stores the size of the address of client (needed to accept socket)
	struct sockaddr_in serv_addr, cli_addr; //Structure containing addr, defined in netinet/in.h - serv_addr has server address and cli_addr client

	sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 

	bzero((char *) &serv_addr, sizeof(serv_addr)); //Init serv_addr to all zero

	//Since we are passing in portnumber through command line, it's a char, we have to switch to int
	portNum = atoi(argv[1]);

	//Set some of the values of the serv_addr struct. 
	serv_addr.sin_family = AF_INET; //Always set to this sucka
	serv_addr.sin_port = htons(portNum); //Set to the port we got and converted
	serv_addr.sin_addr.s_addr = INADDR_ANY; //Set to IP address of the machine

	//Time to bind the program to an address
	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

	//Tell the program to listen on the socket
	listen(sockfd,5); //5 is the maximum value on many systems, easier to be safe

	//printf("Server open on %d\n", portNum);

	clilen = sizeof(cli_addr);

	while(1) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		processId = fork(); //Creating a new thread
		if(processId == 0) { //It was able to create a new fork
			close(sockfd);
			int childProcess = getpid(); //Store the child process for later usage
			//printf("Process Id: %d\n", childProcess);
			newThread(newsockfd, childProcess); //Call the chat function on the socket
			exit(0);
		}
	}
	return 0;
}