/* Project 1 - ChatServer
** Author: Aryan Aziz
** With help from Beej's Guide: http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
** Influenced VERY heavily by: http://www.linuxhowtos.org/C_C++/socket.htm (Their line by line explanation was very helpful)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

//chat function
//Runs the actual chat in each thread
void chat(int socket) {
	int n;
	char receivedMessage[510];
	char sentMessage[500];
	int quit = 0;
	while(quit == 0) {
		bzero(receivedMessage,510);
	   	n = recv(socket,receivedMessage,510,0);
	   	if(n == 0) { //If n = 0 on a read, then the socket has been closed
	   		std::cout << "Client Disconnected" << std::endl;
	   		return;
	   	}
	   	printf("%s",receivedMessage);
	   	std::cout << "Your message: ";
	   	fgets(sentMessage,500,stdin); //Grab the message from the console
	   	if(strstr(sentMessage, "\\quit") == NULL) { //If we did NOT send \quit in the message
	   		n = write(socket,sentMessage,strlen(sentMessage)); //Send it out
	   	}
	   	else {
	   		quit == 1; //Set the quit value to end the while loop
	   		close(socket); //Close the socket
	   		std::cout << "Client Disconnected" << std::endl;
	   		return;
	   	}
   	}
   	return;
}

int main(int argc, char *argv[]) {
	int sockfd; //Listen on this one (file descriptor)
	int newsockfd; //Connect on this one (file descriptor)
	int portNum; //Port number
	int processId; //Process id
	socklen_t clilen; //Stores the size of the address of client (needed to accept socket)
	int n; //Contains number of characters to read/write
	char receivedMessage[500]; //Reads characters from the socket into this array
	struct sockaddr_in serv_addr, cli_addr; //Structure containing addr, defined in netinet/in.h - serv_addr has server address and cli_addr client

	//Make sure we have a port specified
	if(argc < 2) { //argc always = 1, 2+ means we defined items
		std::cout << "Please run the program with a port." << std::endl;
		exit(1); //Quit the program
	}

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

	std::cout << "Waiting for Client to connect..." << std::endl;

	clilen = sizeof(cli_addr);

	//Keep the server running
	while(1) { //Just set some random value that will keep the server constantly running until it gets a sigint
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		processId = fork(); //Creating a new thread to handle the chat.
		if(processId == 0) { //It was able to create a new fork
			std::cout << "Client Connected" << std::endl;
			close(sockfd);
			chat(newsockfd); //Call the chat function on the socket
			exit(0);
		}
		else {
			close(newsockfd);
		} 
	}

	//Close the remaining socket
    close(sockfd);


	return 0;
}