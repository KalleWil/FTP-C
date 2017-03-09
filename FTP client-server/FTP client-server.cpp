#include <stdio.h>
#include <winsock2.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib,"ws2_32.lib")

/* Prototyper*/
char* sendMessage(SOCKET socket_desc, char msg[]);
char* establishConnection(SOCKET socket_desc, WSADATA wsa,struct sockaddr_in server);


int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET socket_desc;
    struct sockaddr_in server;
    
    int file_size, file_desc, recv_size;
    char request_msg[BUFSIZ], reply_msg[BUFSIZ], server_reply[2000], *data;
    
    char userName[] = "USER anonymous\r\n";
    char Password[] = "PASS s133018@dtu.dk\r\n";
    char FILENAME[] = "54wlp.txt\r\n";
    
    establishConnection(socket_desc, wsa, server);
    
    sendMessage(socket_desc, userName);
    sendMessage(socket_desc, Password);
    
    strcpy(request_msg, "Get ");
	strcat(request_msg, FILENAME);
    
    sendMessage(socket_desc, request_msg);
    
    if (strcmp(reply_msg, "OK") == 0) 
    {
        recv(socket_desc, &file_size, sizeof(int), 0);
        data = malloc(file_size);
        file_desc = open(FILENAME, O_CREAT | O_EXCL | O_WRONLY, 0666);
        recv(socket_desc, data, file_size, 0);
        write(file_desc, data, file_size);
        close(file_desc);
	}
	else 
    {

		fprintf(stderr, "Bad request\n");
	}

    
    return 1;
}

char* establishConnection(SOCKET socket_desc, WSADATA wsa, struct sockaddr_in server)
{
    char reply_msg[BUFSIZ];
    
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    else
    {
        printf("WSAStartup initialised.\n");
    }
    
    if((socket_desc = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    else
    {
        printf("Socket created.\n");
    }
    
    server.sin_addr.s_addr = inet_addr("5.179.87.189"); //212.98.95.161//5.179.87.189//130.226.195.126
    server.sin_family = AF_INET;
    server.sin_port = htons( 21 );
    
    /* Forbinder til serveren */
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("Connection Error!");
        return 1;
    }
    else
    {
        printf("Connected to FTP Server\n");
        recv(socket_desc, reply_msg, 150, 0);
        printf("%s\n", reply_msg);
    }
    
    return 1;
}

char* sendMessage(SOCKET socket_desc, char msg[])
{
    char reply_msg[BUFSIZ];
    printf("Sending message %s, with lenght: %i\n", msg, strlen(msg));
    
    send(socket_desc, msg, (int)strlen(msg),0);
    recv(socket_desc, reply_msg, 150, 0);
    
    printf("%s\n", reply_msg);
    printf("End of transmission.\n");

    return reply_msg;
}
