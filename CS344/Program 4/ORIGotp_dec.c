#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void sendText(int sockfd, char fileName[]) {
	char buffer[10];
	FILE *fs = fopen(fileName, "r"); //Open the file
	bzero(buffer, 10);
    int fs_block_sz;
    while((fs_block_sz = fread(buffer, sizeof(char), 10, fs)) > 0) { //Read the file
    	if(send(sockfd, buffer, fs_block_sz, 0) < 0) { //Send the file
            break;
    	}
    	bzero(buffer, 10);
    }
    fclose(fs);
    printf("File Sent\n");
    return;
}

void sendKey(int sockfd, char fileName[]) {
	char buffer[10];
	FILE *fs = fopen(fileName, "r"); //Open the file
	bzero(buffer, 10);
    int fs_block_sz;
    while((fs_block_sz = fread(buffer, sizeof(char), 10, fs)) > 0) { //Read the file
    	if(send(sockfd, buffer, fs_block_sz, 0) < 0) { //Send the file
            break;
    	}
    	bzero(buffer, 10);
    }
    fclose(fs);
    printf("Key Sent\n");
    return;
}

int main(int argc, char *argv[]) {
	//Make sure the key is longer than the input file
	FILE *text = fopen(argv[1], "r");
	FILE *key = fopen(argv[2], "r");
	fseek(text, 0, SEEK_END);
	fseek(key, 0, SEEK_END);
	int textByteCount = ftell(text);
	int keyByteCount = ftell(key);
	fclose(text);
	fclose(key);
	if(keyByteCount < textByteCount) { //
		printf("Error: key '%s' is too short\n", argv[2]);
		exit(1);
	}

	//Get the Socket Setup
	int sockfd; //Listen on this one (file descriptor)
  	int portNum; //Port number
  	int n; //Contains number of characters to read/write
  	struct sockaddr_in serv_addr;
  	struct hostent *server; //Defines the host computer's information

  	sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 
  	portNum = atoi(argv[3]); //Set the portnum from command line arguments
  	server = gethostbyname("localhost");

  	//Set fields in serv_addr again
  	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //Since is a char, you have to use the bcopy to move it from 1 place to the other
	serv_addr.sin_port = htons(portNum);

	//Finally, connect to the socket
  	connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

  	sendText(sockfd, argv[1]);
  	char confirmation[2];
  	bzero(confirmation, 2);
  	n = recv(sockfd,confirmation,2,0);
  	if(confirmation[0] == '1') {
  		sendKey(sockfd, argv[2]);
  	}
	/*char encodedMessage[textByteCount - 1];
	bzero(encodedMessage, textByteCount - 1);
	int m = recv(sockfd,encodedMessage,textByteCount - 1,0);
	printf("%s", encodedMessage);*/	
  	

  	close(sockfd);
	return 0;
}