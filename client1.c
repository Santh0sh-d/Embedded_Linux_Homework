#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define SIZE 64
#define PORT1 4001
#define PORT2 4002
#define PORT3 4003

char buffer[MAX_BUFFER_SIZE];
char *lastValue = NULL;
//Function to create and connect the socket 
int createAndConnectSocket(int port)
{
    int clientfd;
    struct sockaddr_in serverAddr;
    
    // Initialize server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    
    // Create socket for port
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        perror("Error creating socket for port 4001");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) 
    {
        perror("Error connecting to port 4001");
	close(clientfd);
        exit(EXIT_FAILURE);
    }

    return clientfd;
}


// Function to read data from a given socket
void readFromSocket(int port, int sockfd, char *dataFromPort) 
{
//    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead;
    char *token;
   
   // while (1)
    //{
	 bytesRead = read(sockfd, buffer, sizeof(buffer));
	 if (bytesRead <= 0)
	 {
	    perror("Error Reading the data from server");
//	    break;
	 }
    
        // Print the received data to standard output
        //printf("Received Data from port %d = : %s", port, dataFromPort);
       // printf("Received: DONE\n");
     
    //}
     if( strlen(buffer) == 0)
     {
	lastValue = "--";
     }
     else
     {
     token = strtok(buffer, "\n");
  //   char *lastValue = NULL;

     while(token != NULL)
     {
	 lastValue = token;
	 token = strtok(NULL, "\n");
     }
     }
     //dataFromPort = lastValue;
     strncpy(dataFromPort, lastValue, SIZE);
     //printf("LastValue = %s", dataFromPort);
}

int main() 
{
//    pthread_t thread_4001, thread_4002, thread_4003;
    char dataFromPort1[64];
    char dataFromPort2[64];
    char dataFromPort3[64];
    time_t ctime;

    // Create socket for all the ports
    int clientfd1 = createAndConnectSocket(PORT1);
    int clientfd2 = createAndConnectSocket(PORT2);
    int clientfd3 = createAndConnectSocket(PORT3);
   
    while(1)
    {
	// Read data from all three sockets
        readFromSocket(PORT1, clientfd1, dataFromPort1);
        readFromSocket(PORT2, clientfd2, dataFromPort2);
        readFromSocket(PORT3, clientfd3, dataFromPort3);
        
	ctime = time(NULL);
        //printf("###LastValue = %s", dataFromPort1);
	//printf("{\"timestamp\": %ld\t  %s\t %s\t %s\n",ctime, dataFromPort1, dataFromPort2, dataFromPort3 );
  	  printf("{\"timestamp\": %ld\", \"outa\": \"%s\", \"outb\": \"%s\", \"outc\": \"%s\"}\n ", ctime, dataFromPort1, dataFromPort2, dataFromPort3 );
	//printf("{\"timestamp\": %ld, ",ctime);
	//sleep for 100 milliseconds
	usleep(100000);
    }

#if 0
    //Create threads for each port
    pthread_create(&thread_4001, NULL, readFromSocket, &clientfd1);
    pthread_create(&thread_4002, NULL, readFromSocket, &clientfd2);
    pthread_create(&thread_4003, NULL, readFromSocket, &clientfd3);
#endif
    // Close sockets
    close(clientfd1);
    close(clientfd2);
    close(clientfd3);

    return 0;
}

