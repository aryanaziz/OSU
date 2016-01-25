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
  char receivedMessage[512];
  char fullHost[27];
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creates a new socket. First item = address. Second = type. Third = protocol, 0 means OS chooses. Returning -1 means it didn't work. 

  portNum = atoi(argv[2]); //Set the portnum from command line arguments
  sprintf(fullHost, "%s.engr.oregonstate.edu", argv[1]);
  server = gethostbyname(fullHost); //Grabs the server information and holds it into the struct

  //Set fields in serv_addr again
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //Since is a char, you have to use the bcopy to move it from 1 place to the other
  serv_addr.sin_port = htons(portNum);

  //Finally, connect to the socket
  connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

    char* fr_name = "outputfile";
    FILE *fr = fopen(fr_name, "a");
    int fr_block_sz = 0;
  while((fr_block_sz = recv(sockfd, receivedMessage, 512, 0)) > 0) {
    int write_sz = fwrite(receivedMessage, sizeof(char), fr_block_sz, fr);
    if(write_sz < fr_block_sz)
    {
        printf("File write failed on server.\n");
    }
    bzero(receivedMessage, 512);
    if (fr_block_sz == 0 || fr_block_sz != 512) 
    {
        break;
    }
  }
  //Close socket
  printf("Ok received from client!\n");
  close(sockfd);
  return 0;
}