#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "util.h"

#define SIZE 64
#define PORT0 4000
#define PORT1 4001
#define PORT2 4002
#define PORT3 4003

int main() 
{
    char dataFromPort1[SIZE];
    char dataFromPort2[SIZE];
    char dataFromPort3[SIZE];
    time_t ctime;

    // Create socket for UDP port
    int clientfd0 = createAndConnectSocket(PORT0, SOCK_DGRAM_S);
    int clientfd1 = createAndConnectSocket(PORT1, SOCK_STREAM_S);
    int clientfd2 = createAndConnectSocket(PORT2, SOCK_STREAM_S);
    int clientfd3 = createAndConnectSocket(PORT3, SOCK_STREAM_S);
   
    while(1)
    {
	// Read data from all three sockets
        readFromSocket(PORT1, clientfd1, dataFromPort1);
        readFromSocket(PORT2, clientfd2, dataFromPort2);
        readFromSocket(PORT3, clientfd3, dataFromPort3);
        
	float out3Value =  atof (dataFromPort3); 
       // printf ("ATOF val = %.1f", out3Value );
        if (out3Value >= 3.0)
	{
	   //send Frequency data to UDP port 
	   int status = sendToServer(clientfd0, WRITE, OUT1, FREQUENCY, 1);
           if (status == -1)
	   {
              perror("Failed to send data to server ");
	   }

           //Send data to UDP port
	   int status0 = sendToServer(clientfd0, WRITE, OUT1, AMPLITUDE, 8000); 
           if (status0 == -1)
	   {
              perror("Failed to send data to server ");
	   }
           
	}
	else if (out3Value < 3.0)
	{
	   //send Frequency data to UDP port 
	   int status1 = sendToServer(clientfd0, WRITE, OUT1, FREQUENCY, 2); 
           if (status1 == -1)
	   {
              perror("Failed to send data to server ");
	   }
           
           //Send data to UDP port
	   int status2 = sendToServer(clientfd0, WRITE, OUT1, AMPLITUDE, 4000); 
           if (status2 == -1)
	   {
              perror("Failed to send data to server ");
	   }
	}
        
	ctime = time(NULL);
  	printf("{\"timestamp\": %ld\", \"out1\": \"%s\", \"out2\": \"%s\", \"out3\": \"%s\"}\n ", ctime, dataFromPort1, dataFromPort2, dataFromPort3 );
	
        //sleep for 20 milliseconds
	usleep(20000);
    }

    // Close sockets
    close(clientfd1);
    close(clientfd2);
    close(clientfd3);

    return 0;
}

