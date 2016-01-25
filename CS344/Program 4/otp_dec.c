//OTP Decode - Client
//Author: Aryan Aziz
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

//Send Text Function, sends the text file to the server
void sendText(int sockfd, char fileName[]) {
	char buffer[10];
	FILE *fs = fopen(fileName, "r"); //Open the file
	bzero(buffer, 10);
    int fs_block_sz;
    int bytesSent;
    while((fs_block_sz = fread(buffer, sizeof(char), 10, fs)) > 0) { //Read the file
    	if((bytesSent = send(sockfd, buffer, fs_block_sz, 0)) < 0) { //Send the file
            break;
    	}
    	bzero(buffer, 10);
    }
    if(bytesSent == 10) { //Check if we sent 10 bytes at the end, server code ends when we DON'T send 10 bytes 
    	send(sockfd, "0", 1, 0); //If we did, send one more null packet to end the server's transmission
    }
    fclose(fs);
    //printf("File Sent\n");
    return;
}

//Send Key function, sends the key file to the server
void sendKey(int sockfd, char fileName[]) {
	char buffer[10];
	FILE *fs = fopen(fileName, "r"); //Open the file
	bzero(buffer, 10);
    int fs_block_sz;
    int bytesSent;
    while((fs_block_sz = fread(buffer, sizeof(char), 10, fs)) > 0) { //Read the file
    	if((bytesSent = send(sockfd, buffer, fs_block_sz, 0)) < 0) { //File has been sent
            break;
    	}
    	bzero(buffer, 10);
    }
    if(bytesSent == 10) { //Check if we sent 10 bytes at the end, server code ends when we DON'T send 10 bytes 
    	send(sockfd, "0", 1, 0); //If we did, send one more null packet to end the server's transmission
    }
    fclose(fs);
    //printf("Key Sent\n");
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
	char type[2];
	bzero(type, 2);
	n = recv(sockfd,type,2,0); //Get the server's type

	if(type[0] == 'd') { //If it's the decode server
		sendText(sockfd, argv[1]); //Send the text
		char confirmation[2];
		bzero(confirmation, 2);
		n = recv(sockfd,confirmation,2,0); //Wait for confirmation
		if(confirmation[0] == '1') { //If we got confirmation
			sendKey(sockfd, argv[2]); //Send the key
		}
		//Get the decoded message back
		char encodedMessage[textByteCount];
		bzero(encodedMessage, textByteCount);
		int m = recv(sockfd,encodedMessage,textByteCount - 1,0);
		sprintf(encodedMessage, "%s\0", encodedMessage);
		printf("%s", encodedMessage);
		printf("\n");
	}
	else { //If it isn't the decode server
    	printf("Could not connect to otp_dec_d\n");
    	exit(2);
    }
  	
  	close(sockfd);
	return 0;
}