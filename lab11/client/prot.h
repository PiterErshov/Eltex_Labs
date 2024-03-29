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
#define RCVBUFSIZE 32
unsigned short outPort;	
char *sendOut;
unsigned short broadcastPort;
char *broadcastIP, *outIP;
pthread_mutex_t mutex;

int search_target(int x, int y, int Mx, int My, char **map);

void * broadcast_send(void *agv);

void * broadcast_recv(void *agv);//широковещательная функция поиска клиентов

void *TCPcon(void *agv);

void freeMas(char **mas, int y); //очистка массива
