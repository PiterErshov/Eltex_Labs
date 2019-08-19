#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 1024
#define minr 1
#define maxr 10

struct msgbuf
{
	long mtype;
	int mSum[N];
} buf;

void bees(int bee_p, int shmid, int i);

void bear(int h_p, int lt, int shmid);
