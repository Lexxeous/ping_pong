#include "pingpong.h"

const int GLOB_BUF_LEN = 4096;

int sendMessage(struct ConnectionInfo* con, char* msg)
{
	if(con == NULL || msg == NULL)
	{
		return 1;
	}

	send(con->socket, msg, strlen(msg), 0);

	return 0;
}

//------------------------------------------------------------------------------------------

char* recieveMessage(struct ConnectionInfo* con)
{
	char* buffer = (char*)malloc(GLOB_BUF_LEN);
	memset(buffer, '\0', GLOB_BUF_LEN); // Clear the buffer.

	if(con == NULL)
	{
		return 1;
	}

	recv(con->socket, buffer, GLOB_BUF_LEN, 0);

	return buffer;
}
 
//------------------------------------------------------------------------------------------

void dealocate_message(char* mem)
{
	free(mem);
}
 
//------------------------------------------------------------------------------------------

int connect_to_server(char* who, int port, struct ConnectionInfo* con)
{
	int sockfd;
	struct sockaddr_in server_addr;
	struct hostent* hent;

	// Error check the port number.
	if(port < 10001) 
	{
		printf("Port ≥ 10000 required.\n");
		return 1;
	}

	if((hent=gethostbyname(who)) == NULL) 
	{
		printf("Invalid host name.\n");
		return 1;
	}
	
	// Create the client socket.
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Socket error.\n");
		return 1;
	}
	
	memset((void*) &server_addr, 0, sizeof(server_addr)); // Clear the server address structure.
	
	// Set up the server address structure.
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr = *((struct in_addr*)hent->h_addr);
	server_addr.sin_port = htons(port);

	if(connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) 
	{
		printf("Connect error.\n");
		return 1;
	}

	con->socket = sockfd;

	return 0;
}
 
//------------------------------------------------------------------------------------------

int run_server(int port)
{
	// Set up the socket.
	int sockfd, newsockfd; //fd = file descriptor
	unsigned int client_length;

	// Structures for client and server addresses.
	struct sockaddr_in server_addr, cli_addr;
	struct ConnectionInfo con;
	
	// Create the server socket.
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) // fail if return -1
	{
		printf("Socket error.\n");
		return 1;
	}
	
	memset((void*) &server_addr, 0, sizeof(server_addr)); // Clear the server address structure.
	
	// Set up the server address structure.
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	
	// Bind the socket to the server address and port.
	if(bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) 
	{
		printf("Bind error.\n");
		return 1;
	}
	
	// Listen on the socket, queue 10 incoming connections.
	listen(sockfd, 10);
	
	if(fork() == 0) // 0 is the child process
	{
		return 0;
	}

	client_length = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &client_length);
	if(newsockfd < 0)
	{
		printf("Accept error.\n");
		return 1;
	}

	// Loop forever, handling connections.
	while(1)
	{
		char* msg;
		char* buffer = (char*)malloc(GLOB_BUF_LEN); // 
		memset(buffer, '\0', GLOB_BUF_LEN); // Clear the buffer.

		con.socket = newsockfd;
		con.buf = buffer;
		con.buf_length = GLOB_BUF_LEN;

		msg = recieveMessage(&con);

		if(!strcmp(msg, "ping") || !strcmp(msg, "PING"))
		{
			sendMessage(&con, "pong");
		}
		else
		{
			sendMessage(&con, msg);
		}
		dealocate_message(msg);
	}

	return 0; // shouldnt ever run
}



