#ifndef UTIL_H
#define UTIL_H
typedef enum socktype_s
{
    SOCK_STREAM_S = 1,
    SOCK_DGRAM_S
}socktype_t;

typedef enum operation {
    READ = 1,
    WRITE
}Opts_t;

typedef enum property {
    FREQUENCY,
    AMPLITUDE
}Prop_t;

typedef enum object {
    OUT1,
    OUT2
}Obj_t;


typedef struct message {
    uint16_t operation;
    uint16_t object;
    uint16_t property;
    uint16_t value;
}Msg_t;


int createAndConnectSocket(int port, socktype_t sockType);
void readFromSocket(int port, int sockfd, char *dataFromPort);
int sendToServer(int clientfd, uint16_t opts, uint16_t obj, uint16_t prop, uint16_t value);

#endif
