#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define MESSSIZE 255//Array size for message
#define PORTMASS 5//Array size for port number

char *message; //message for the client of the second type
unsigned short Port;//clients port 
char *IP,//clients IP 
    *TCP_IP,//servers IP 
    TCPport[PORTMASS];//port for TCP connection
pthread_mutex_t mutex;

struct mess //structure for message
{
    int time;
    int size;
    char message[MESSSIZE];
};

void * broadcast_recv(void *agv);//broadcast function of waiting for an invitation from the server

void *TCPcon(void *agv);//TCP connection
