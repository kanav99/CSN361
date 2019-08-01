#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 

#define PORT 8080 

/*
 * Main Function
 */
int main(int argc, char const *argv[]) 
{ 
	if (argc != 2) {
		printf("Usage: %s \"<message to server>\"\n", argv[0]);
		exit(0);
	}
	int sock = 0; 
	struct sockaddr_in server_address;
	// To store the incoming messages
	char buffer[1024] = {0}; 
	// Make a new socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("ERROR: Unable to create a socket");
        exit(EXIT_FAILURE);
	}

	// Binding port and family to server address
	server_address.sin_family = AF_INET; 
	server_address.sin_port = htons(PORT); 
	
	// 
	if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr)<=0) {
        perror("ERROR: invalid address");
        exit(EXIT_FAILURE);
	}

	// Connect to server
	if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("ERROR: Couldn't connect to server");
        exit(EXIT_FAILURE);
	}

	send(sock , argv[1] , strlen(argv[1]) , 0 );

	read( sock , buffer, 1024); 
	printf("%s\n",buffer ); 

	return 0; 
} 

