#ifndef UTIL_H
#define UTIL_H
typedef enum socktype_s
{
    SOCK_STREAM_S = 1,
    SOCK_DGRAM_S
}socktype_t;

int createAndConnectSocket(int port, socktype_t sockType);
void readFromSocket(int port, int sockfd, char *dataFromPort);

#endif
