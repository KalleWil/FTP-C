// FTP client-server.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <stdio.h>
#include <stdio.h>
#include <winsock2.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME 	"a.txt"
#define SERVER_IP 	"130.226.195.126"
#define SERVER_PORT 	21

int main(int argc, char *argv[])
{
	int 	socket_desc;
	struct 	sockaddr_in server; //
	char 	request_msg[BUFSIZ], reply_msg[BUFSIZ];

	int	file_size, file_desc;
	char	*data;

	socket_desc = socket(AF_INET, SOCK_STREAM, 0); //AF_INET (designate the type of addresses that is used ipv4/ipv6 or IPX) AF_INET = ipv4) // Third agrument 0 is the protocol and should always be 0 //

	if (socket_desc == -1)
	{
		perror("Could not create socket");
		return 1;
	}

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	// Connect to server
	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("Connection failed");
		return 1;
	}

	return 0;
}


