#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 

#define PORT 8080 

/*
 * Main Function
 */
int main(int argc, char const *argv[]) 
{ 
	int server, client; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	// Buffer to store incoming messages
	char buffer[1024] = {0}; 
	// message to send
	char *hello = "Hello from the other side"; 
	
	// Create a new socket
	if (!(server = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("ERROR: Unable to create a socket.");
        exit(EXIT_FAILURE);
	}
	
	// Checking port
	if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("ERROR: Cannot bind to port 8080, port might already be used.");
        exit(EXIT_FAILURE);
	}

	// Binding the server properties
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Bind the socket to port
	if (bind(server, (struct sockaddr *)&address, sizeof(address))<0) {
		perror("ERROR: Cannot bind to port 8080, port might already be used.");
		exit(EXIT_FAILURE);
	}

	// Listen for connections
	if (listen(server, 3) < 0) {
        perror("ERROR: Couldn't listen");
        exit(EXIT_FAILURE);
	}

	// Loop to accept infinite connections
	while (1) {
		if ((client = accept(server, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
	        perror("ERROR: Couldn't accept");
	        exit(EXIT_FAILURE);
		}

		read(client, buffer, 1024); 
		printf("Client: %s\n",buffer ); 
		send(client , hello , strlen(hello) , 0 ); 
	}

	return 0; 
} 
