#include "pingpong.h"

const int GLOB_BUF_LEN = 4096; // global variable to allocate different amounts of chars

int sendMessage(struct ConnectionInfo* con, char* msg)
{
	if(con == NULL || msg == NULL) // dont allow empty structs or messages
	{
		return 1;
	}

	send(con->socket, msg, strlen(msg), 0); // send the message

	return 0; // return successfully
}

//------------------------------------------------------------------------------------------

char* receiveMessage(struct ConnectionInfo* con)
{
	char* buffer = (char*)malloc(GLOB_BUF_LEN); // allocate message memory
	memset(buffer, '\0', GLOB_BUF_LEN); // clear the buffer

	if(con == NULL) // dont allow empty struct
	{
		return "Error: Connection info is NULL.\n";
	}

	recv(con->socket, buffer, GLOB_BUF_LEN, 0); // receive the message

	return buffer; // return what was sent
}
 
//------------------------------------------------------------------------------------------

void dealocate_message(char* mem)
{
	free(mem); // free (deallocate) message memory
}
 
//------------------------------------------------------------------------------------------

int connect_to_server(char* who, int port, struct ConnectionInfo* con)
{
	int sockfd;
	struct sockaddr_in server_addr;
	struct hostent* hent;

	// error check the port number
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
	
	// create the client socket.
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) // create socket with IPv4 and stream configuration
	{
		printf("Socket error.\n");
		return 1;
	}
	
	memset((void*) &server_addr, 0, sizeof(server_addr)); // clear the server address structure
	
	// set up the server address structure.
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr = *((struct in_addr*)hent->h_addr);
	server_addr.sin_port = htons(port);

	if(connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) 
	{
		printf("Connect error.\n");
		return 1;
	}

	con->socket = sockfd;

	return 0; // return successfully
}
 
//------------------------------------------------------------------------------------------

int run_server(int port)
{
	// set up the socket
	int sockfd, newsockfd; //fd = file descriptor
	unsigned int client_length;

	// structures for client and server addresses.
	struct sockaddr_in server_addr, cli_addr;
	struct ConnectionInfo con;
	
	// create the server socket.
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) // fail if return -1
	{
		printf("Socket error.\n");
		return 1;
	}
	
	memset((void*) &server_addr, 0, sizeof(server_addr)); // clear the server address structure
	
	// set up the server address structure
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	
	// bind the socket to the server address and port
	if(bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) 
	{
		printf("Bind error.\n");
		return 1;
	}
	
	// listen on the socket, queue 10 incoming connections
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

	// loop forever, handling connections
	while(1)
	{
		char* msg;
		char* buffer = (char*)malloc(GLOB_BUF_LEN); // allocate message memory
		memset(buffer, '\0', GLOB_BUF_LEN); // clear the buffer

		// set up ConnectionInfo structure for the server
		con.socket = newsockfd;
		con.buf = buffer;
		con.buf_length = GLOB_BUF_LEN;

		msg = receiveMessage(&con);

		if(!strcmp(msg, "ping")) // if clent sends "ping"
		{
			sendMessage(&con, "pong"); // server responds with "pong"
		}
		else // for every other string
		{
			sendMessage(&con, msg); // server responds with what was sent
		}
		dealocate_message(msg); // free (deallocate) message memory
	}

	return 0; // shouldnt ever run
}



