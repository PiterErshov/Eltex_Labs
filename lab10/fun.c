#include "prot.h"

void *fighter(void *arg)
{
	int i = *(int *) arg, res, pt = 0;
	void *status;

	//printf("Thread %d ready\n", i);
	fflush(stdout);
	pthread_mutex_lock(&put.mutex[i]);
	while (flag > 0)
	{
		pthread_cond_wait(&cond, &put.mutex[i]);
	}
	pthread_mutex_unlock(&put.mutex[i]);
	//*     
	pthread_mutex_lock(&put.mutex[i]);
	if (put.live > 1)
	{
		while (1)
		{
			srand(i * time(NULL));
			srand(rand());
			pt = rand() % put.live;
			if (pt != i && put.kill[pt] == 0)
				break;
		}
		printf("Thread %d kill thread %d\n", i, pt);
		//fflush(stdout);
		pthread_cancel(put.threads[pt]);
		put.kill[pt] = 1;
		put.live--;
		put.w = i;
	}
	else
		pthread_exit(NULL);
	pthread_mutex_unlock(&put.mutex[i]);
	/*
	   int j = 0;
	   while(j < put.max)
	   {    
	   printf("THREAD %d :KILLED[%d] = %d\n", i, j, put.kill[j]);
	   fflush (stdout);
	   j++;
	   }
	   // */
	//pthread_mutex_lock(&put.mutex[i]);
	pthread_exit(NULL);
}
