#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define N 1024

struct put
{
	pthread_mutex_t mutex;	
	char data[N][N];
} put;

void *fighter(void *arg);
