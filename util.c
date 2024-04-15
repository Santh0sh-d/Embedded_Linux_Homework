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

int sendToServer(int clientfd, uint16_t opts, uint16_t obj, uint16_t prop, uint16_t value)
{
    struct sockaddr_in serverAddr;
    // Initialize server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4000);

    Msg_t *msg;
    msg = (Msg_t*) malloc(sizeof(Msg_t));
    if (msg == NULL)
    {
       perror("Error allocating memory");
       return -1;
    }
    msg->operation = htons(opts);
    msg->object  = htons(obj);
    msg->property = htons(prop);
    msg->value = htons(value);

    size_t bytes_sent = sendto(clientfd, msg, sizeof(msg), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bytes_sent == -1)
    {
       perror("Error sending data");
       free(msg);
       return -1;
    }

    //Free the memory
    free(msg);

    return 0;
}

