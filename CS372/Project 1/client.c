/* Project 1 - ChatClient
** Author: Aryan Aziz
** With help from Beej's Guide: http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
** Influenced VERY heavily by: http://www.linuxhowtos.org/C_C++/socket.htm (Their line by line explanation was very helpful)
** There are a lot less comments here because I commented pretty much every line of server, and a lot of the code is the same.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int sockfd; //Listen on this one (file descriptor)
  int portNum; //Port number
  int n; //Contains number of characters to read/write
  int quit = 0;
  struct sockaddr_in serv_addr;
  struct hostent *server; //Defines the host computer's information
  char username[11];
  char sentMessage[500];
  char fullMessage[510]; //The typed message and username together
  char receivedMessage[500];

  bzero(username, 11);
  printf("What's your username: ");
  fgets(username, 10, stdin);
  char *pos;
  if((pos=strchr(username, '\n')) != NULL) { //Because fgets adds a newline char at the end, use this if to replace it with another \0
    *pos = '\0';
  }
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 

  portNum = atoi(argv[2]); //Set the portnum from command line arguments
  server = gethostbyname(argv[1]); //Grabs the server information and holds it into the struct

  //Set fields in serv_addr again
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //Since is a char, you have to use the bcopy to move it from 1 place to the other
  serv_addr.sin_port = htons(portNum);

  //Finally, connect to the socket
  connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
  printf("Connected To Server\n");

  //The Chat Loop
  //Very similar to the server's chat loop, except I tried to keep this one all in the main loop instead of separate function
  //This was done on purpose to see how different it would be
  while(quit == 0) {
    printf("Your Message: ");
    bzero(sentMessage,500);
    fgets(sentMessage,500,stdin); //Grab the message
    sprintf(fullMessage,"%s >> %s", username, sentMessage); //Put the username >> in front 
    if(strstr(sentMessage, "\\quit") == NULL) { //If they DON'T write \quit
      //Write it to server
      n = write(sockfd,fullMessage,strlen(fullMessage));
      //Response from server
      bzero(receivedMessage,500);
      n = recv(sockfd,receivedMessage,500,0); //Since we are hardcoding the server's name, no extra 10 chars needed
      if(n == 0) { //n = 0 means the server quitted you
        printf("Disconnected From Server\n");
        quit = 1;
      }
      else {
        printf("ChatServ >> %s",receivedMessage);
      }
    }
    else { //If they did write \quit
      quit = 1;
    }
  }
  //Close socket
  close(sockfd);
  return 0;
}