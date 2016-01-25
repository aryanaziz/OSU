#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

int getFile(int socket, int processId) {
	char fr_name[10];
	bzero(fr_name, 10);
	char receivedMessage[10];
	sprintf(fr_name, "%dt", processId);
	FILE *fr = fopen(fr_name, "a"); //Create the file
	int fr_block_sz = 0; 
	while((fr_block_sz = recv(socket, receivedMessage, 10, 0)) > 0) {
		int write_sz = fwrite(receivedMessage, sizeof(char), fr_block_sz, fr); //Write to the file
		if(write_sz < fr_block_sz) {
		    fprintf(stderr, "File write failed on server.\n");
		}
		bzero(receivedMessage, 10);
		if (fr_block_sz == 0 || fr_block_sz != 10) {
		    break;
		}
	}
	fclose(fr);
	FILE *text = fopen(fr_name, "r");
	fseek(text, 0, SEEK_END);
	int numChars = ftell(text);
	fprintf(stderr, "File '%s' Transfer Complete\n", fr_name);
	return numChars;
}

void getKey(int socket, int processId) {
	char fr_name[10];
	bzero(fr_name, 10);
	char receivedMessage[10];
	sprintf(fr_name, "%dk", processId);
	FILE *fr = fopen(fr_name, "a"); //Create the file
	int fr_block_sz = 0; 
	while((fr_block_sz = recv(socket, receivedMessage, 10, 0)) > 0) {
		fprintf(stderr, "Received %d bytes", fr_block_sz);
		int write_sz = fwrite(receivedMessage, sizeof(char), fr_block_sz, fr); //Write to the file
		if(write_sz < fr_block_sz) {
		    fprintf(stderr, "File write failed on server.\n");
		}
		bzero(receivedMessage, 10);
		if (fr_block_sz == 0 || fr_block_sz != 10) {
		    break;
		}
	}
	fclose(fr);
	fprintf(stderr, "File '%s' Transfer Complete\n", fr_name);
	return;
}

void encode(int processId, int numChars, int socket) {
	char fileArray[numChars - 1]; //-1 because of the newline char at the end of the file
	char keyArray[numChars - 1]; //Same as above
	char encodedArray[numChars - 1];
	int i = 0;
	int c;

	char fr_name[10];
	bzero(fr_name, 10);
	sprintf(fr_name, "%dt", processId);

	FILE *fr = fopen(fr_name, "r");
	while((c = fgetc(fr)) != EOF && i < numChars - 1) {
		fileArray[i] = c;
		i++;
	}
	fclose(fr);


	char kr_name[10];
	bzero(kr_name, 10);
	sprintf(kr_name, "%dk", processId);

	int j = 0;
	int d;
	FILE *kr = fopen(kr_name, "r");
	while((d = fgetc(kr)) != EOF && j < numChars - 1) {
		keyArray[j] = d;
		j++;
	}
	fclose(kr);
	//char letters[27] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
	char letters[28];
	sprintf(letters, "ABCDEFGHIJKLMNOPQRSTUVWXYZ ");
	

	for(i = 0; i < numChars - 1; i++) {
		int sum = 0;
		for(j = 0; j < 28; j++) {
			if(fileArray[i] == letters[j]) {
				sum = sum + j + 1;
			}
			if(keyArray[i] == letters[j]) {
				sum = sum + j + 1;
			}
		}
		int remainder = sum % 27;
		encodedArray[i] = letters[remainder];
		fprintf(stderr, "%c", letters[remainder]);
	}

	char encodedMessage[numChars];
	bzero(encodedMessage, numChars);
	sprintf(encodedArray, "%s\n", encodedArray);
	//encodedArray[numChars - 1] = "\n";
	printf("\n%s", encodedArray);
	int n = write(socket,encodedArray,numChars - 1); //Send it Back
	return;
}

void newThread(int socket, int processId) {
	fprintf(stderr, "Getting file from pid %d\n", processId);
	int numChars = getFile(socket, processId);
	char confirmation[2];
  	bzero(confirmation,1);
  	sprintf(confirmation, "1");
  	int n;
  	n = write(socket,confirmation,strlen(confirmation)); //Tell the client to move on
	fprintf(stderr, "Getting key from pid %d\n", processId);
	getKey(socket, processId);
	encode(processId, numChars, socket);
	/*char message[37];
	bzero(message, 37);
	sprintf(message, "THE RED GOOSE FLIES AT MIDNIGHT STOP");
	n = write(socket,message,strlen(message));*/
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
			int childProcess = getpid();
			fprintf(stderr, "Process Id: %d\n", childProcess);
			newThread(newsockfd, childProcess); //Call the chat function on the socket
			exit(0);
		}
	}
	return 0;
}