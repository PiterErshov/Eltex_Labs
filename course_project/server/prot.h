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
#define N 50
unsigned short bPort1, bPort2;
char *broadcastIP, *TCPport_one, *TCPport_two;	/* IP broadcast address */
pthread_cond_t cond_flag; 
int flag;

struct mess
{
    int time;
    int size;
    char message[MESSSIZE];
};
struct mess m1, m2;
struct msgbuf
{
	long mtype; 
    int size;
    int size_of;
	struct mess m[N];
} buf;

void * broadcast_type1(void *agv);

void * broadcast_type2(void *agv);

void * broadcast_s(void *agv);

void *TCPconOne(void *agv);

void *TCPconTwo(void *agv);

void *TCPrecvOne(void *agv);

void *TCPsendTwo(void *agv);

char * map_creat(int x, int y);

void freeMas(char **mas, int y); //очистка массива
