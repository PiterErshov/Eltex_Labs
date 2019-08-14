#include "prot.h"

void *fighter(void *arg)
{
	int i = *(int*)arg, res, pt = 0;
	void *status;
	
	printf("Thread %d ready\n", i);
	fflush(stdout);
	pthread_mutex_lock(&put.mutex[i]);
	while(1)
	{
		pthread_cond_wait(&cond, &put.mutex[i]);
	}
	pthread_mutex_unlock(&put.mutex[i]);
	//if (i == put.max - 1)
		//pthread_cond_broadcast(&put.cond);
	/*	
	while (1)
	{
		srand(i * time(NULL));
		srand(rand());
		pt = rand() % put.max;
		if (pt != i && put.kill[pt] == 0)
			break;
	}
	printf("Thread %d kill thread %d\n", i, pt);
	//fflush(stdout);
	pthread_cancel(put.threads[pt]);
	put.kill[pt] = 1;
	/*int j = 0;
	while(j < put.max)
	{	
		printf("THREAD %d :KILLED[%d] = %d\n", i, j, put.kill[j]);
		fflush (stdout);
		j++;
	}*/
	/*pthread_mutex_lock(&put.mutex[i]);
	put.w = i;
	pthread_mutex_unlock(&put.mutex[i]);*/
	pthread_exit(NULL);
}
