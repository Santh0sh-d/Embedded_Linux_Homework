#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "util.h"

#define MAX_BUFFER_SIZE 512
#define SIZE 64

char buffer[MAX_BUFFER_SIZE];
char *lastValue = NULL;

//Function to create and connect the socket
int createAndConnectSocket(int port, socktype_t sockType)
{
    int clientfd;
    struct sockaddr_in serverAddr;

    // Initialize server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    // Create socket for port
    clientfd = socket(AF_INET, sockType, 0);
    if (clientfd == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    if (sockType == SOCK_STREAM_S)
    {
        // Connect to the server
        if (connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
        {
        perror("Error connecting to port");
        close(clientfd);
        exit(EXIT_FAILURE);
        }
    }

    return clientfd;
}

// Function to read data from a given socket
void readFromSocket(int port, int sockfd, char *dataFromPort)
{
    ssize_t bytesRead;
    char *token;

    bytesRead = read(sockfd, buffer, sizeof(buffer));
    if (bytesRead <= 0)
    {
        perror("Error Reading the data from server");
    }

    if (strlen(buffer) == 0)
    {
       lastValue = "--";
    }
    else
    {
       token = strtok(buffer, "\n");

       while (token != NULL)
       {
           lastValue = token;
           token = strtok(NULL, "\n");
       }
    }

    strncpy(dataFromPort, lastValue, SIZE);
}
