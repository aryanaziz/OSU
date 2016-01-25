#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int sockfd; //Listen on this one (file descriptor)
  	int portNum; //Port number
  	struct sockaddr_in serv_addr;
  	struct hostent *server; //Defines the host computer's information
  	char fullHost[27];
  	int n;

  	sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 

  	portNum = atoi(argv[2]); //Set the portnum from command line arguments
	//sprintf(fullHost, "%s.engr.oregonstate.edu", argv[1]);
	//server = gethostbyname(fullHost); //Grabs the server information and holds it into the struct
	server = gethostbyname(argv[1]);

	//Set fields in serv_addr again
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //Since is a char, you have to use the bcopy to move it from 1 place to the other
	serv_addr.sin_port = htons(portNum);

	//Finally, connect to the socket
  	connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

  	if(strcmp(argv[3], "-l") == 0) { //ls
  		char sentMessage[10];
  		bzero(sentMessage,10);
  		sprintf(sentMessage, "l %s", argv[4]);
  		n = write(sockfd,sentMessage,strlen(sentMessage));
  	}
  	else { //get file

  	}

	return 0;
}