#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define N 1024

struct put
{
	pthread_mutex_t mutex[N];	
	pthread_t threads[N];
	int kill[N];	
	int max;
	char data[N][N];
	int w;
} put;

void *fighter(void *arg);
