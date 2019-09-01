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

#define MESSSIZE 255//Array size for message
#define BROADPORTS 10//number of ports for clients
#define N 10//message queue size
unsigned short bPort1, bPort2;
char *broadcastIP, *TCPport_one, *TCPport_two;
pthread_mutex_t mutex;
int size_of;//queue size flag
long mtype;//flag for message queue

struct msgbuf//structure for message queue
{
    int time;
    int size;
    char message[MESSSIZE];
} buf;

void * broadcast_type1(void *agv);//broadcast function for first type clients

void * broadcast_type2(void *agv);//broadcast function for second type clients

void *TCPconOne(void *agv);//connection function for clients of the first type

void *TCPconTwo(void *agv);//connection function for clients of the second type

void *TCPrecvOne(void *agv);//function of receiving messages from clients of the first type

void *TCPsendTwo(void *agv);//function of sending a message to clients of the second type
