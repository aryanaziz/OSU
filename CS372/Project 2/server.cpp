/* Project 1 - FTP Server
** Author: Aryan Aziz
** With help from Beej's Guide: http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fcntl.h> 

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

	std::cout << "Server open on " << portNum << std::endl;

	clilen = sizeof(cli_addr);

	//Keep the server running
	while(1) { 
		//The main socket (control)
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		

		char buffer[512];
		char* fs_name = argv[2];
		FILE *fs = fopen(fs_name, "r");
	    if(fs == NULL)
	    {
	        printf("ERROR: File %s not found.\n", fs_name);
	        exit(1);
	    }

	    bzero(buffer, 512);
	    int fs_block_sz;
	    while((fs_block_sz = fread(buffer, sizeof(char), 512, fs)) > 0) {
	    	if(send(newsockfd, buffer, fs_block_sz, 0) < 0) {
	    		//fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", fs_name, errno);
	            break;
	    	}
	    	bzero(buffer, 512);
	    }
	    printf("Ok File %s from Client was Sent!\n", fs_name);

        
    }

    return 0;
}



