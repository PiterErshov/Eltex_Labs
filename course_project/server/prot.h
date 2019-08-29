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
#define N 50
unsigned short broadcastPort;
char *broadcastIP;	/* IP broadcast address */
pthread_cond_t cond_flag; 
int flag;

struct br_mess
{
    char TCPport_one[PORTMASS];
    char TCPport_two[PORTMASS];
}BM;

struct mess
{
    int time;
    int size;
    char message[MESSSIZE];
};

struct msgbuf
{
	long mtype; 
    int size;
    int size_of;
	struct mess m[N];
} buf;
/*
void Print(const Q* queue)
{
   const COM* node = queue->head;
 
   for (; node; node = node->next)
   {
      printf("%d ", node->value);
   }
   printf("\n");
}
*/
void * broadcaster(void *agv);

void * broadcast_s(void *agv);

void *TCPconOne(void *agv);

void *TCPconTwo(void *agv);

char * map_creat(int x, int y);

void freeMas(char **mas, int y); //очистка массива
