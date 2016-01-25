ReadMe.txt

Code was influenced heavily by both Beej's guide (http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html) and Linux How-Tos (http://www.linuxhowtos.org/C_C++/socket.htm).



To compile:
Server: g++ -o server server.cpp
Client: gcc -o client client.c


To run:
Server: ./server [PORT] 
Client: ./client [HOSTNAME] [PORT] 


When running the server, it will display that the server is running and awaiting connections. When you run the client, it will first ask for a username and will then connect to the server. A message should display on BOTH the client and server stating that the client has connected. 

The client will be allowed to send their message first. After this, the server may respond, and so on and so fourth. 

Typing "\quit" on the server or client when it's its appropriate time to respond will result in disconnecting the client (A message will be displayed on the server) and the client program will end. 