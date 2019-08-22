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

#define MAXRECVSTRING 255
#define MAXPENDING 5
#define RCVBUFSIZE 32
unsigned short broadcastPort;
char *broadcastIP;	/* IP broadcast address */
char *TCPport;	/* String to broadcast */
int flag;

void * broadcaster(void *agv);

void * broadcast_s(void *agv);//широковещательная функция поиска клиентов

void *TCPcon(void *agv);
