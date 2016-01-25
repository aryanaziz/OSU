ReadMe.txt

Author: Aryan Aziz

There are 2 files again:
server.cpp
client.c


To compile:
	Server:
		g++ -o server server.cpp
	Client:
		gcc -o client client.c


To run:
	It should be based on the Example Execution method. 
		Start the server with: ./server <portnum>
		Start the client and specify an item: ./client <server> <portnum> <flag> <portnum>
			OR: ./client <server> <portnum> <flag> <filename> <portnum>
		It should then either list the directory or send the file (if it exists)


