/* Project 2 - FTP Server
** Author: Aryan Aziz
** With help from Beej's Guide: http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
** File directory ported from this post: http://www.linuxquestions.org/questions/programming-9/c-list-files-in-directory-379323/
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
#include <string>
#include <dirent.h>
#include <vector>

int fileFound = 0;

void sendListDirectory(int port) {
	int sockfd; //Listen on this one (file descriptor)
	int newsockfd; //Connect on this one (file descriptor)
	int n;

	socklen_t clilen; //Stores the size of the address of client (needed to accept socket)
	struct sockaddr_in serv_addr, cli_addr; //Structure containing addr, defined in netinet/in.h - serv_addr has server address and cli_addr client

	sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 

	bzero((char *) &serv_addr, sizeof(serv_addr)); //Init serv_addr to all zero

	//Set some of the values of the serv_addr struct. 
	serv_addr.sin_family = AF_INET; //Always set to this sucka
	serv_addr.sin_port = htons(port); //Set to the port we got and converted
	serv_addr.sin_addr.s_addr = INADDR_ANY; //Set to IP address of the machine

	//Time to bind the program to an address
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "ERROR ON BINDING" << std::endl;
	}

	//Tell the program to listen on the socket
	listen(sockfd,5); //5 is the maximum value on many systems, easier to be safe

	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd < 0) {
		std::cout << "ERROR ON ACCEPT" << std::endl;
	}
	std::cout << "Sending directory contents on port " << port << std::endl;
	char sentMessage[512];
  	bzero(sentMessage,512);

  	std::string dir = std::string(".");
  	std::vector<std::string> files = std::vector<std::string>();

  	DIR *dp; //To find the directory information
  	struct dirent *dirp; //Create a struct
  	if((dp = opendir(dir.c_str())) == NULL) {
  		std::cout << "Error" << std::endl;
  	}

  	while((dirp = readdir(dp)) != NULL) {
  		files.push_back(std::string(dirp->d_name));
  		sprintf(sentMessage, "%s\n%s ", sentMessage, dirp->d_name); //Write it to the message
  		//std::cout << dirp->d_name << std::endl;
  		//printf("%s", sentMessage);

  	}
  	closedir(dp);
  	
  	/*for(int j = 0; j < files.size(); j++) {
  		std::cout << files[j] << std::endl;
  	}*/

  	//sprintf(sentMessage, "This is a sample message to send for file listing\0");
  	//n = write(newsockfd,sentMessage,strlen(sentMessage));
  	n = write(newsockfd,sentMessage,strlen(sentMessage)); //Write it to the server
	close(sockfd); //Close the socket
	close(newsockfd); //Close the socket
}

void sendFile(int port, std::string fileName) {
	int sockfd; //Listen on this one (file descriptor)
	int newsockfd; //Connect on this one (file descriptor)
	int n;

	socklen_t clilen; //Stores the size of the address of client (needed to accept socket)
	struct sockaddr_in serv_addr, cli_addr; //Structure containing addr, defined in netinet/in.h - serv_addr has server address and cli_addr client

	sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 

	bzero((char *) &serv_addr, sizeof(serv_addr)); //Init serv_addr to all zero

	//Set some of the values of the serv_addr struct. 
	serv_addr.sin_family = AF_INET; //Always set to this sucka
	serv_addr.sin_port = htons(port); //Set to the port we got and converted
	serv_addr.sin_addr.s_addr = INADDR_ANY; //Set to IP address of the machine

	//Time to bind the program to an address
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "ERROR ON BINDING" << std::endl;
	}

	//Tell the program to listen on the socket
	listen(sockfd,5); //5 is the maximum value on many systems, easier to be safe

	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd < 0) {
		std::cout << "ERROR ON ACCEPT" << std::endl;
	}

	char buffer[512];

	FILE *fs = fopen(fileName.c_str(), "r"); //Open the file
    if(fs == NULL) //If it doesn't exist
    {
        std::cout << "File not found. Sending error message" << std::endl;
        fileFound = 1;
        exit(1);
    }

    std::cout << "Sending " << fileName << "to " << port << std::endl;

    bzero(buffer, 512);
    int fs_block_sz;
    while((fs_block_sz = fread(buffer, sizeof(char), 512, fs)) > 0) { //Read the file
    	if(send(newsockfd, buffer, fs_block_sz, 0) < 0) { //Send the file
            break;
    	}
    	bzero(buffer, 512);
    }
    std::cout << "Ok, File: " << fileName << " was sent!" << std::endl;
    close(sockfd);
	close(newsockfd);
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

	std::cout << "Server open on " << portNum << std::endl;

	clilen = sizeof(cli_addr);

	//Keep the server running
	while(1) { 
		//The main socket (control)
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		std::cout << "Client Connected" << std::endl;

		int n;
		char receivedMessage[100];
		n = recv(newsockfd,receivedMessage,100,0);

		if(receivedMessage[0] == 'l') { //If it's ls
			std::string delimiter = " "; //break the string down
			std::string s(receivedMessage);
			size_t pos = 0;
			std::string token;
			while((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());
			}
			int port = atoi(s.c_str()); //Set the port after breaking down the string
			std::cout << "List directory requested on port " << port << std::endl;
			sendListDirectory(port); //Call the function to send it. 
		}
		else {
			std::string delimiter = " ";
			std::string s(receivedMessage); 
			size_t pos = 0;
			std::string token;
			int x = 0;
			std::string fileName;
			while((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());
				if(x == 1) {
					fileName = token; //Grab the file name
				}
				x++;
			}
			int port = atoi(s.c_str()); //grab the port
			std::cout << "File " << fileName <<" requested on port " << port << std::endl;
			sendFile(port, fileName); //Call the send file function
			if(fileFound == 1) { //If the file sending returned a null
				fileFound = 0;
				char sentMessage[15];
  				bzero(sentMessage,15);
  				sprintf(sentMessage, "FILE NOT FOUND");
  				n = write(newsockfd,sentMessage,strlen(sentMessage)); //Send it over
			}
		}

	    //End file transfer
        
    }

    close(sockfd);
    close(newsockfd);

    return 0;
}