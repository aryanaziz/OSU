/* Project 2 - FTPClient
** Author: Aryan Aziz
** With help from Beej's Guide: http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
** Influenced VERY heavily by: http://www.linuxhowtos.org/C_C++/socket.htm (Their line by line explanation was very helpful)
** There are a lot less comments here because I commented pretty much every line of server, and a lot of the code is the same.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

void getListDirectory(int port, char fullHost[]) {
	int sockfd, n; //Listen on this one (file descriptor)
	struct sockaddr_in serv_addr;
  	struct hostent *server; //Defines the host computer's information
  	sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 

  	server = gethostbyname(fullHost); //Grabs the server information and holds it into the struct

  	//Set fields in serv_addr again
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //Since is a char, you have to use the bcopy to move it from 1 place to the other
	serv_addr.sin_port = htons(port);

	//Finally, connect to the socket
	if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		printf("Error connecting");
	}

	char receivedMessage[512];
	bzero(receivedMessage, 512);
	while((n = recv(sockfd,receivedMessage,512,0)) > 0){ //Grab the message
		printf("%s\n", receivedMessage); //Print it
		bzero(receivedMessage, 512);
	}
}

void getFile(int port, char fullHost[], char fileName[]) {
	int sockfd, n; //Listen on this one (file descriptor)
	struct sockaddr_in serv_addr;
  	struct hostent *server; //Defines the host computer's information
  	sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 

  	server = gethostbyname(fullHost); //Grabs the server information and holds it into the struct

  	//Set fields in serv_addr again
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //Since is a char, you have to use the bcopy to move it from 1 place to the other
	serv_addr.sin_port = htons(port);

	//Finally, connect to the socket
	if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		printf("Error connecting");
	}

	char receivedMessage[512];

	char* fr_name = fileName; //Grab the file name
	if(access(fr_name, F_OK) != -1) { //See if the file already exists
		printf("File Already Exists\n");
		return;
	}

	//If the file doesn't already exist
    FILE *fr = fopen(fr_name, "a"); //Create the file
    int fr_block_sz = 0; 
	while((fr_block_sz = recv(sockfd, receivedMessage, 512, 0)) > 0) {
		int write_sz = fwrite(receivedMessage, sizeof(char), fr_block_sz, fr); //Write to the file
		if(write_sz < fr_block_sz) {
		    printf("File write failed on server.\n");
		}
		bzero(receivedMessage, 512);
		if (fr_block_sz == 0 || fr_block_sz != 512) {
		    break;
		}
	}
	printf("File transfer complete.\n");
	return;
}

int main(int argc, char *argv[]) {
  int sockfd; //Listen on this one (file descriptor)
  int portNum; //Port number
  int n; //Contains number of characters to read/write
  int quit = 0;
  struct sockaddr_in serv_addr;
  struct hostent *server; //Defines the host computer's information
  char receivedMessage[512];
  char fullHost[10]; //Change this back to 27...
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 

  portNum = atoi(argv[2]); //Set the portnum from command line arguments
  //sprintf(fullHost, "%s.engr.oregonstate.edu", argv[1]);
  sprintf(fullHost, "%s", argv[1]);
  server = gethostbyname(fullHost); //Grabs the server information and holds it into the struct

  //Set fields in serv_addr again
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //Since is a char, you have to use the bcopy to move it from 1 place to the other
  serv_addr.sin_port = htons(portNum);

  //Finally, connect to the socket
  connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

  if(strcmp(argv[3], "-l") == 0) { //If the command is LS
  	char sentMessage[100];
  	bzero(sentMessage,100);
  	sprintf(sentMessage, "l %s", argv[4]);
  	n = write(sockfd,sentMessage,strlen(sentMessage)); //Tell the server what to do
  	printf("Receiving directory structure from %s:%s\n", argv[1], argv[4]);
  	int port = atoi(argv[4]); //Grab the port
  	getListDirectory(port, fullHost); //Call the function
  }
  if(strcmp(argv[3], "-g") == 0) { //Get file
  	char sentMessage[100];
  	bzero(sentMessage,100);
  	char errorMessage[15];
  	bzero(errorMessage,15);
  	sprintf(sentMessage, "g %s %s", argv[4], argv[5]);
  	n = write(sockfd,sentMessage,strlen(sentMessage)); //Tell the server what to do
  	int port = atoi(argv[5]);
  	printf("Receiving %s from %s:%s\n", argv[4], argv[1], argv[5]);
  	getFile(port, fullHost, argv[4]); //Call the function
  	/*while((n = recv(sockfd, errorMessage, 15, 0)) > 0) { //If there is an error finding the file
  		printf("%s:%s says %s", argv[1], argv[2], errorMessage); //Display the message
  	}*/
  }
  else { //Anything other than g or l. 
  	printf("That is not a valid command\n");
  }

  //End File Transfer
  //Close socket
  close(sockfd);
  return 0;
}