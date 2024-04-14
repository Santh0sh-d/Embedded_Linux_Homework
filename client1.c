#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#define SIZE 64
#define PORT1 4001
#define PORT2 4002
#define PORT3 4003


int main() 
{

    char dataFromPort1[SIZE];
    char dataFromPort2[SIZE];
    char dataFromPort3[SIZE];
    time_t ctime;

    // Create socket for all the ports
    int clientfd1 = createAndConnectSocket(PORT1, SOCK_STREAM_S);
    int clientfd2 = createAndConnectSocket(PORT2, SOCK_STREAM_S);
    int clientfd3 = createAndConnectSocket(PORT3, SOCK_STREAM_S);
   
    while(1)
    {
	// Read data from all three sockets
        readFromSocket(PORT1, clientfd1, dataFromPort1);
        readFromSocket(PORT2, clientfd2, dataFromPort2);
        readFromSocket(PORT3, clientfd3, dataFromPort3);
        
	ctime = time(NULL);
        printf("{\"timestamp\": %ld\", \"out1\": \"%s\", \"out2\": \"%s\", \"out3\": \"%s\"}\n ", ctime, dataFromPort1, dataFromPort2, dataFromPort3 );

	//sleep for 100 milliseconds
	usleep(100000);
    }

    // Close sockets
    close(clientfd1);
    close(clientfd2);
    close(clientfd3);

    return 0;
}

