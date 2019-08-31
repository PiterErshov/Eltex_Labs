#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define MAXRECVSTRING 255
#define MAXPENDING 5
#define RCVBUFSIZE 32
#define MESSSIZE 255
#define PORTMASS 5
#define BROADPORTS 10
#define N 10
unsigned short bPort1, bPort2;
char *broadcastIP, *TCPport_one, *TCPport_two;
pthread_mutex_t mutex;
int size_of;

struct msgbuf
{
	long mtype; 
    int time;
    int size;
    char message[MESSSIZE];
} buf;

void * broadcast_type1(void *agv);

void * broadcast_type2(void *agv);

void * broadcast_s(void *agv);

void *TCPconOne(void *agv);

void *TCPconTwo(void *agv);

void *TCPrecvOne(void *agv);

void *TCPsendTwo(void *agv);
